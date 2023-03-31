dir >> loco


"C:\Program Files\Microchip\xc16\v1.70\bin\xc16-gcc.exe"   ../target/codigo.c  -o build/default/production/_ext/1472/codigo.o  -c -mcpu=24FJ64GA002  -MP -MMD -MF "build/default/production/_ext/1472/codigo.o.d"        -g -omf=elf -DXPRJ_default=default  -legacy-libc    -O0 -msmart-io=1 -Wall -msfr-warn=off    >> out.txt

"C:\Program Files\Microchip\xc16\v1.70\bin\xc16-gcc.exe"   -o dist/default/production/Main.X.production.elf  build/default/production/_ext/1472/codigo.o      -mcpu=24FJ64GA002        -omf=elf -DXPRJ_default=default  -legacy-libc    -Wl,,,--defsym=__MPLAB_BUILD=1,,--script=p24FJ64GA002.gld,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="dist/default/production/Main.X.production.map",--report-mem,--memorysummary,dist/default/production/memoryfile.xml  


::"C:\Program Files\Microchip\xc16\v1.70\bin"\\xc16-bin2hex dist/default/production/Main.X.production.elf -a  -omf=elf   -mdfp="C:/Program Files (x86)/Microchip/MPLABX/v5.30/packs/Microchip/PIC24F-GA-GB_DFP/1.1.74"/xc16 
"C:\Program Files\Microchip\xc16\v1.70\bin"\\xc16-bin2hex dist/default/production/Main.X.production.elf -a  -omf=elf   
