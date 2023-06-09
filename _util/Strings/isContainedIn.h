/*RFI JSon
{
	'Nombre': 'isContainedIn',
	'NombreToolBox': 'isContainedIn',
	'Tipo' : 'SistemFnc',
	'title': 'Return the position where the substring begin inside the string. Return -1 if it isn´t contained.',
	'returnInfo': {'type':'int16_t','tooltip':'Position.'},
	'parameters': [{'name': 'Substring',
					'tooltip': 'Substring.',
					'required': 'true"',
					'type': 'char*'},
                    {'name': 'String',
					'tooltip': 'The string where we´ll search the substring.',
					'required': 'true"',
					'type': 'char*'}],
	'InnerHTML':"
		<div type='int16_t' originalclass='funcion' class='lineaDeCodigo' definir='useisContainedInV1' originalid='isContainedIn' draggable='true' ondragstart='drag_linea(event)'>
			Text.IsContainedIn(<div type='char*' title='Substring to find' class='parametroDiv'></div>,<div type='char*' title='String where search.' class='parametroDiv'></div>)
		</div>"
}
*/