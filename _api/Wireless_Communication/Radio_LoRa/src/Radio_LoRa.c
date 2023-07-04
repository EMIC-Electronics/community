/*****************************************************************************

  @file     Radio_LoRa.c

  @brief    Radio LoRa API driver

  @author   Pentacolo Tomas

  @date     04/07/2023

  @version  v1.0.0 - Initial Release
  
 ******************************************************************************/

/*==================[inclusions]=============================================*/


void rfSleep()
{
	radioSleepFlag = 1;
	RFM96_Sleep();

}

void pRF()
{	
	//	static uint8_t miAck=1;
	//	miTx.senderAddress=id;
	//	miTx.receiverAddress=idDestino;
	//	miTx.retries = reintentos;
	//	miTx.preambuleLengthHightByte  = 0X00;
	//	miTx.responseRequest=miAck;
	//	miAck++;
	//	miTx.fragmentado = 0;	
	//	miTx.message[0]='A';
	//	miTx.message[1]='B';
	//	miTx.message[2]='C';
	//	miTx.message[3]='D';
	//	miTx.message[4]='E';
	//	miTx.messageLength=5;
	//	miTx.socketAvailable=false;
	
		
	char d;
	char *r;
	radio_return_t rv = RF_ERROR;
	radioBuffer_t *new_out_frame = NULL;
	if (RADIO_BUFFER_OUT_FREE_MEM > 8)// si hay espacio como para poner por lo menos el encabezado del paquete
	{
		rv = radioBuffer_OUT_new(&new_out_frame);// inicio el nodo
		if(rv == RF_OK)
		{
			rv = radioBuffer_OUT_push(new_out_frame , messageTypeScript);
			if (rv == RF_OK)
			{
				rv = radioBuffer_OUT_push(new_out_frame , idDestino); // idDestino
			}
			if (rv == RF_OK)
			{
				rv = radioBuffer_OUT_push(new_out_frame , radioTry);
			}
			if (rv == RF_OK)
			{
				rv = radioBuffer_OUT_push(new_out_frame , 0x00); // preambuleLengthHightByte
			}

			for (r = ptr_param[0];*r > 0 && rv == RF_OK; r++)
			{
				rv = radioBuffer_OUT_push(new_out_frame,*r);
			}
			if (rv == RF_OK)
			{
				rv = radioBuffer_OUT_push(new_out_frame,'\t');
			}
			for (r = ptr_param[1];*r > 0 && rv == RF_OK; r++)
			{
				rv = radioBuffer_OUT_push(new_out_frame,*r);
			}
			if(n_param>2 && rv == RF_OK)
			{
				uint8_t s2xH,s2xL;
				while(param_l[2] && rv == RF_OK)
				{
					s2xH=*ptr_param[2];
					if(s2xH>='A')
						s2xH-=('A'-10);
					else
						s2xH-='0';
					ptr_param[2]++;

					s2xL=*ptr_param[2];
					if(s2xL>='A')
						s2xL-=('A'-10);
					else
						s2xL-='0';
					ptr_param[2]++;
					param_l[2]-=2;

					d=(s2xH<<4)|(s2xL);

					rv = radioBuffer_OUT_push(new_out_frame,d);
				}
			}
			if (rv == RF_ERROR)
			{
				//se quedo sin memoria, pero pudo meter por lo menos en encabezado
				radioBuffer_OUT_free(new_out_frame);
			}
			else
			{
				radioBuffer_OUT_end(new_out_frame);
			}
		}
		else
		{
			//se quedo sin frames
		}
	}
	else
	{
		// se quedo sin memoria antes de hacer el new
		// todo ver de devolver un error para que se pueda enviar mas tarde
	}
}

radioBuffer_t *get_script_node;
void gRF()
{
	char r;
	radio_return_t rv = RF_OK;
	if (radioBuffer_IN_is_sending(get_script_node))
	{
		putc_rsp('�');//'«');
		while (rv == RF_OK)
		{
			rv = radioBuffer_IN_pop(get_script_node, &r);
			if(rv == RF_OK)
			{
				putc_rsp(r);
			}
		}
		putc_rsp('�');//'»');
	}
	else
	{
		// todo devolver un error para que se sepa que no se pudo leer el dato
	}
	//radioBuffer_FRAME_IN_pop();
}

void setIds()
{	
	id=atol(ptr_param[0]);
	idGrupo=atol(ptr_param[1]);
	RFM96_set_ids(id,idGrupo);
}

void WupRF()
{
	RFM96W_Init();
}




#newRFIcode(_templates\BufferRing.h,nombre=RadioSend,len=32,StrmOut=null,StrmIn=Radio.Send,FrameIdn=NULL)
#newRFIcode(_templates\BufferRing.h,nombre=RadioRcv,len=32,StrmOut=Radio.Read,StrmIn=null,FrameIdn=NULL)
radioBuffer_t *current_out_frame = NULL;
radioBuffer_t *current_in_frame = NULL;
radioApi_estados_rx_t estado_rf_rx = RF_API_RX_NUEVO_FRAME;
radioApi_estados_tx_t estado_rf_tx = RF_API_TX_NUEVO_FRAME;
void RadioPoll (void)
{
	Poll_RF();
	if (radioSleepFlag == 1)
	{
		radioBuffer_IN_init();
		radioBuffer_OUT_init();
		miTx.socketAvailable = true;
		miRx.socketAvailable = true;
		ackTx.socketAvailable = true;
		RFM96_Sleep();
		__delay_ms(100);
	}

	static uint8_t miAck=1;
	static uint8_t retriesAux=0;
	switch(estado_rf_tx)
	{
	case RF_API_TX_ENVIO_FRAME:
		if (miTx.socketAvailable == 1)//si esta libre el socket
		{
			if (radioBuffer_OUT_is_sending(current_out_frame) && current_out_frame != NULL)//si hay datos en de un frame anterior
			{
				uint32_t x;
				for(x=2;x<maxMsgLength;x++)
				{
					if(RF_OK != radioBuffer_OUT_pop(current_out_frame , &miTx.message[x]))// extraigo un byte del nodo que estoy transmitiendo
					{
						miTx.controlByte |= ultimoPaquete;// se�alizo que es el ultimo paquete, porque llego al final del frame
						radioBuffer_OUT_free(current_out_frame);// pongo el nodo en free, porque ya esta para enviar
						estado_rf_tx = RF_API_TX_NUEVO_FRAME;
						break;
					}
				}
				if (miTx.receiverAddress != idGrupo )// si no es un id grupal, configuro el ack
				{
					miTx.responseRequest=miAck;
					miAck++;
					if (miAck == 0)
						miAck++;
				}
				else
				{
					miTx.responseRequest = 0;
				}
				miTx.message[0] = miTx.streamingId;
				miTx.message[1] = miTx.controlByte;
				miTx.retries = retriesAux;
				miTx.messageLength = x;
				miTx.socketAvailable = 0;// se�alizo que hay datos pendientes para enviar
			}
			else
			{
				estado_rf_tx = RF_API_TX_NUEVO_FRAME;
			}
		}
		break;
	case RF_API_TX_NUEVO_FRAME:
		if( radioBuffer_OUT_have_frames())// si hay frames pendientes para enviar
		{
			radio_return_t rv = RF_ERROR;

			rv = radioBuffer_OUT_Next_Frame(&current_out_frame);// tengo que buscar el siguiente frame
			if (rv == RF_OK)
			{

				rv = radioBuffer_OUT_pop(current_out_frame,&(miTx.streamingId));  // tipo de paquete;
				if (rv == RF_OK)
				{
					rv = radioBuffer_OUT_pop(current_out_frame,&(miTx.receiverAddress));
				}
				if (rv == RF_OK)
				{
					rv = radioBuffer_OUT_pop(current_out_frame,&(retriesAux));
				}
				if (rv == RF_OK)
				{
					rv = radioBuffer_OUT_pop(current_out_frame,&(miTx.preambuleLengthHightByte));
				}
				miTx.senderAddress = id;
				miTx.controlByte &= (~ultimoPaquete);
				if(RF_OK != rv)
				{
					// falto algun dato del encabezado de rf
					radioBuffer_OUT_free(current_out_frame);// borro el nodo, porque esta roto
				}
				else
				{
					radioBuffer_OUT_sending(current_out_frame);//marco el nodo para saber que se esta enviando
					estado_rf_tx = RF_API_TX_ENVIO_FRAME;
				}
			}
			else
			{
				// hay nodos enviandose
				estado_rf_tx = RF_API_TX_ENVIO_FRAME;
			}
		}
		else // si no hay frames pendientes, agrego un frame con el streaming
		{
			if( RING_RadioSend_notEmpty )// si tengo datos del streaming pendientes
			{
				radio_return_t rv = RF_ERROR;
				radioBuffer_t *new_out_frame = NULL;
				rv = radioBuffer_OUT_new(&new_out_frame);
				if (rv == RF_OK)// si me entrego el nodo
				{
					rv = radioBuffer_OUT_push(new_out_frame,messageTypeBuffer);
					if (rv == RF_OK)
					{
						rv = radioBuffer_OUT_push(new_out_frame,idDestino); // idDestino
					}
					if (rv == RF_OK)
					{
						rv = radioBuffer_OUT_push(new_out_frame,radioTry);
					}
					if (rv == RF_OK)
					{
						rv = radioBuffer_OUT_push(new_out_frame,0x00); // preambuleLengthHightByte
					}
					if (rv == RF_END)// si no se armo bien el encabezado
					{
						// se quedo sin memoria y no pudo guardar el encabezado de rf
						radioBuffer_OUT_free(new_out_frame);
					}
					while( RING_RadioSend_cont > 0 && rv == RF_OK )
					{
						rv = radioBuffer_OUT_push(new_out_frame, RING_RadioSend_pop());
					}
					if (rv == RF_OK)
					{
						radioBuffer_OUT_end(new_out_frame);//cierro el nodo, para que sea enviado
					}
					else
					{
						// se genero un error mientras se cargaban los datos del frame, pero pero por lo menos tiene el encabezado
						// error state sin memoria de salida
						radioBuffer_OUT_free(new_out_frame);//cierro el nodo, para que sea enviado
					}

				}
				else// si no me entrego el nodo
				{
					// error state sin nodos de salida
					estado_rf_tx = RF_API_TX_ENVIO_FRAME;// me voy a enviar frames, asi libero algun nodo
				}
			}
			else
			{
				estado_rf_tx = RF_API_TX_ENVIO_FRAME;

			}
		}

		break;

	}

	switch(estado_rf_rx)
	{
	case RF_API_RX_ENVIO_FRAME:
	{
		if( radioBuffer_IN_have_frames())// si hay frames pendientes para leer
		{
			radio_return_t rv = RF_ERROR;
			radioBuffer_t *new_in_frame = NULL;
			rv = radioBuffer_IN_Next_Frame(&new_in_frame);// tengo que buscar el siguiente frame
			if ( rv == RF_OK)
			{
				char mensaje_buffer[16];
				char mensaje_index=0;
				uint8_t flag_mensaje_incorrecto = 0;

				uint8_t dato=0;
				do
				{
					rv = radioBuffer_IN_pop(new_in_frame, &dato);
					if (rv == RF_OK)
					{
						if ( mensaje_index > 15 )
						{
							// error en el mensaje, el nombre del mensaje es mayor a 16 bytes
							// error state identificador del mensaje muy largo
							radioBuffer_IN_free(new_in_frame);// libero el nodo, porque esta roto
							rv = RF_ERROR;
							break;
						}
					}
					else
					{
						// error state le falta el \t al mensaje
						radioBuffer_IN_free(new_in_frame);// descarto el mensaje, porque no llego al \t
						break;
					}
					mensaje_buffer[mensaje_index] = dato;
					mensaje_index++;
				}while ( mensaje_buffer[mensaje_index-1] != '\t');

				if (rv == RF_OK)
				{
					mensaje_buffer[mensaje_index-1] = 0x00;
					puts_f("#eRF(");
					for (mensaje_index = 0; mensaje_buffer[mensaje_index] != 0x00 ; mensaje_index++ )
					{
						putc_f(mensaje_buffer[mensaje_index]);
					}
					get_script_node = new_in_frame;// le paso el puntero para que el script lo lea
					radioBuffer_IN_sending(get_script_node);
					puts_f(");\r");
					radioBuffer_IN_free(get_script_node);//libero el nodo, porque ya se envio al script
					estado_rf_rx = RF_API_RX_NUEVO_FRAME;// veo si tengo otro frame para enviar
				}
				else
				{
					// llamar al evento de error
				}
			}
			else
			{
				// tengo un nodo abrierto, y siguen llegando datos
				estado_rf_rx = RF_API_RX_NUEVO_FRAME;// veo si tengo otro frame para enviar
			}
		}
		else
		{
			estado_rf_rx = RF_API_RX_NUEVO_FRAME;// veo si tengo otro frame para enviar
		}
	}
	break;

	case RF_API_RX_NUEVO_FRAME:
	{
		if ( miRx.socketAvailable == 0)// si tengo un dato pendiente para leer del modulo de rf
		{
			int i;
			radio_return_t rv = RF_ERROR;
			miRx.streamingId=miRx.message[0];
			miRx.controlByte=miRx.message[1];
			switch(miRx.streamingId)
			{
			case messageTypeScript:

				if (radioBuffer_IN_is_sending(current_in_frame))
				{
					rv = RF_OK;// si esta llegando mas paquetes del mismo frame, sigo llenando el mismo nodo
				}
				else
				{
					rv = radioBuffer_IN_new(&current_in_frame);// pido un nuevo nodo
				}
				if (rv == RF_OK)// si me pudo entregar un nuevo nodo
				{
					if (miRx.messageLength <= RADIO_BUFFER_IN_FREE_MEM)
					{
						for(i = 2 ; i < miRx.messageLength && rv == RF_OK ; i++)
						{
							rv = radioBuffer_IN_push(current_in_frame,miRx.message[i]);
						}
						if (rv == RF_ERROR)
						{
							// se quedo sin memoria la cola de entrada
							// error state sin memoria de entrada
							radioBuffer_IN_free(current_in_frame);// borro el paquete, porque no entro entero
							estado_rf_rx = RF_API_RX_ENVIO_FRAME; // voy a enviar, asi libero espacio
						}
						else
						{
							if (miRx.controlByte & ultimoPaquete)  // si es último pongo fin FRAME
							{
								radioBuffer_IN_end(current_in_frame);//cierro el nodo
								estado_rf_rx = RF_API_RX_ENVIO_FRAME;
							}
							else
							{
								radioBuffer_IN_sending(current_in_frame);// marco el nodo para saber que aun no llego todo el frame
							}
						}
					}
					else
					{
						// no tiene espacio para meter el paquete que llego, tengo que esperar a que se consuman los datos
						// error state sin memoria de entrada
						radioBuffer_IN_free(current_in_frame);// borro el paquete, porque no entro entero
						estado_rf_rx = RF_API_RX_ENVIO_FRAME;//voy a enviar, asi libero espacio
					}
				}
				else
				{
					//nos quedamos sin nodos
					// assert
#ifdef DEBUG

					uint8_t i;
					while(1)
					{
						i++;
					}
#endif
					// error state sin nodos de entrada
					// hay que esperar a que se liberen mas nodos
					estado_rf_rx = RF_API_RX_ENVIO_FRAME;
				}
				break;
			case messageTypeBuffer:
				for(i = 2 ; i < miRx.messageLength ; i++)
				{
					if (STRM_RadioRcv_WORD_COUNT>0)
					{
						STRM_RadioRcv_WORD_COUNT--;
						if (STRM_RadioRcv_WORD_COUNT==0)
						{
							STRM_RadioRcv_END_INTERRUPT = 1;
						}
					}
					RING_RadioRcv_push(miRx.message[i]);
				}

				break;

			}
			miRx.socketAvailable = 1;// marco que ya se leyo el mensaje
		}
		else
		{
			estado_rf_rx = RF_API_RX_ENVIO_FRAME;
		}
	}
	break;

	}

}


void Api_RF_Init()
{
	//srand(miTx -> senderAddress);
	radioSleepFlag = 0;
	miTx.socketAvailable=1;
	miTx.waitingForAck=0;
	ackTx.socketAvailable=1;
	miRx.socketAvailable=1;
	radioBuffer_IN_init();
	radioBuffer_OUT_init();
}