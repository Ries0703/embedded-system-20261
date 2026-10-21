# **<u>Chapter 3: ARM Cortex-M4 programming</u>** 

❑ Introduction 

- ❑ ARM Cortex-M 

- ❑ STM32F429 Microcontroller 

- ❑ STM32F429I-DISCOVERY Development Kit 

- ❑ Programming with STM32F429 

_We’re going to read a lot of datasheet!_ 

**1** 

**ES, NLT 2026** 

# **<u>8 bit vs 32 bit microcontrollers</u>** 

- ❑ 8 bit MCUs: (8051, PIC, AVR, STM8…) 

   - l Low cost, simple hardware and software. 

   - l Low performance (10-20 MHz), small data bus (8 bit), low availability of peripherals. 

   - l Suitable for simple and low-cost applications: toys, consumer products,... 

   - l VD: Arduino classic boards 

- ❑ 32 bit MCUs: (ARM-based, PIC32, AVR32,...) 

   - l 32 bit instruction set and operands, 32 bit data bus: much higher performance. 

   - l High clock rate (100-200 MHz). 

   - l Large availability of peripherals. 

   - l Suitable for more complicated system with multi-task, data acquisition and processing, and better connectivity. 

- ❑ Most popular 32-bit MCU: ARM-based microcontroller 

**2** 

**ES, NLT 2026** 

# **<u>ARM-powered products</u>** 

**3** 

**ES, NLT 2026** 

# **<u>ARM processor portfolio</u>** 



<!-- Start of picture text -->
System i Cortex-A73iw Applicationprocessors<br>capability & i) ith MMU<br>performance 4 rtex-A72) Cy mets<br>Cortex-AlSis Cortex-;CoRRES wt MSsupport mobile Linux, OS)<br>Cortex-Al7 Cortex-A32<br>tag | Cortex-A35<br>Ww Cortex-A9 | | Cortex-A12<br>Cortex-A8 Cortex-A7 Cortex-R8&<br>Cortex-A5J LJ RealTime<br>' LJ processors<br>ARMII™YW ) wu Cortex-R7<br>ARM926™ “Oo. ed Cortex-R5<br>_} ortex-R4 ed Microcontrollers<br>]<br>ARM920T™, lad Cortex-M4i) Cortex-M7 andembedded deeply<br>‘™ =|<br>ARM940T { ARM946™, Cortex-M3 all<br>| ARM966™ =) ib0 Cortex-mo+<br>ARI i seriesee Cortex-M!(FPGA)<br>Classic ARM Processors ARM Cortex Processors<br><!-- End of picture text -->

# **Classification of ARM processors** 

**4** 

**ES, NLT 2026** 

# **<u>ARM Cortex Processors</u>** 

- ❑ ARM Cortex- **A** family: 

Applications processors for full-fledge high performance (Linux, Android…) with clock rate > 1 GHz. 

- ❑ ARM Cortex- **R** family: 

Embedded processors for real-time systems that requires absolute stability and safety in operation, clock rate usually of 200 MHz – 1 GHz. 

- ❑ ARM Cortex- **M** family: 

Microcontroller for embedded system, clock rate < 200 MHz. 

**5** 

**ES, NLT 2026** 

# **<u>Cortex family</u>** 

### **Cortex-A8** 

- Architecture v7A 

- ▪ MMU 

- AXI 

- VFP & NEON support 



<!-- Start of picture text -->
ores Osboa ew<br>=<br>Leal ee Jo He]<br>te] BlacGg<br>L~ J<br>ooo===| el ese Ee<br><<br>JTai Bra<br>[rr Ls]<br>CORTEX™-A8<br>!<br>ax<br><!-- End of picture text -->

#### **Cortex-R4** 

- Architecture v7R 

- MPU (optional) 

- AXI 

- Dual Issue 



<!-- Start of picture text -->
InterfaceDebu<br>Prefetch i<br>& Branch i<br>Predictionait | | EWsuce<br>c. [BRR coMemon<br>xo cache Es = Cache<br>2 —<br>°<br>rr<br><!-- End of picture text -->

### **Cortex-M3** 

- Architecture v7M 

- MPU (optional) 

- AHB Lite & APB 



<!-- Start of picture text -->
ARM<br>: viewer<br>| owe | Single wie<br>My7 Dou] Fasbee<br>x t<br>c<br>-o<br>° ‘SRAM<br>S| interace peripheral VF<br><!-- End of picture text -->

**6** 

**ES, NLT 2026** 

# **<u>ARM Cortex-M</u>** 

# ❑ Some typical components/peripherals on Cortex-M MCU 



<!-- Start of picture text -->
On-chip Flash JTAG debug<br>Serial wire debug (SWD) and<br>Cortex-M3<br>Power management, RTC, reset and watchdog, internal<br>oscillator, and PLL<br>USB 2.0 interface Two CAN channels<br>12-bit A/D converter<br>(16 channels) Three USART channels<br>10/100 Ethernet MAC Two channelsSPI and forSSI I2C, |2S,<br>SD/MNC card interface; 16-bitincluding standard PWM timers<br>80 GPIO Pins<br><!-- End of picture text -->

**7** 

**ES, NLT 2026** 

# **<u>Some MCUs designed based on Cortex-M4</u>** 

- <u>Analog Devices</u> ADUCM4050 

- <u>Cypress</u> 6200, FM4 

- <u>Infineon XMC4000</u> 

- <u>Maxim</u> Darwin 

- <u>Microchip (Atmel)</u> SAM4C/4E/G5, SAMD5/E5x 

- <u>Nordic</u> nRF52 

- <u>Nuvoton</u> NuMicro M480 

- <u>NXP LPC4000, LPC4300</u> LPC54000 

- <u>NXP</u> (Freescale) Kinetis K, V3, V4 

- <u>Renesas</u> S3, S5, S7, RA4, RA6 

- <u>Silicon Labs</u> (Energy Micro) EFM32 Wonder 

- <u>ST STM32</u> F3, F4, L4, L4+, G4, WB 

- <u>Texas Instruments</u> LM4F, TM4C, MSP432, CC13x2R, CC1352P, CC26x2R 

- <u>Toshiba</u> TX04 

**8** 

**ES, NLT 2026** 

**<u>STM32F429xxx block diagram</u>** 



<!-- Start of picture text -->
ola= =e5 Su {ame J T=p=|E=<br>Sat eo =; ERED<br>|- cr ee<br>F=_1- He AS<br>nee |<br>soCae, =] =fale peas<br>~ Plea]<br>~~ lea] hteresaa = ee<br>=O]<br>f=] | eo KS<br>.<br>a ~~ona as= Tl ——} iL_, befbef = KS...KB.<br>Ss Gee] i emer ee<br>a<br>aangeT QL) bef ae = KO<br>ee — bef ee Kae,<br>d=. lot en<br>——<br>anne Oe TS al gece Su<br>= 2e=-r Pt ly a<br><!-- End of picture text -->

**9** 

**ES, NLT 2026** 

# **<u>STM32F429xx</u>** 



<!-- Start of picture text -->
ee ed<br>|e _|freee cane DEE EEE<br>[erred] oxso0s oc00 - oxsrr FFF<br>xsons OFF<br>oueree cere [TiaCortBlock? tiope xs 0000<br>nteral a ed<br>FE FFE serereral coor FFE<br>nDx€000 9000<br>2000 0000<br>oxcrer FFF<br>sr2MtejeBlockFue $<br>Groite Beer S12 ctonz 000<br>Peer pucteaae [Reena} oxtoot 600. onsoon FFF<br>curt‘0x8000 0000 stLen a weete (Qet001 6BFF<br>Block<br>FNC bark312<br>GnarrFxe000 2000FRE rk?<br>S120Block2<br>14000OrF  a000 Peniperate<br>FEF S12AtoyeeBlock? \<br>21a goo S12-Mbyte,=a [__ResenesSRAM(et KB asec_| ox2002.0000-oxz002FFFEox2003 0000. onsFFF FFF [Reserved] oatooscaton0 00002000 |-ox4000 FFFF<br>pa) (SUASRAM(16 KB ctened 0x2001 COD - 0x2001 FFFF onsonn TERE<br>fxc009 0000 ‘SRAM [__By btReserve(112bepanding banding KB atszed ____|| oxz000IFFF 0000-02001COOF - xt FFFBFFFFF<br>[ |[Option —"Resenes SisBy t es erhaterox FF 7a10- C000 - OxtFFFxt FFF TF Coos<br>[Reserved][Reserves]evmemagy | rieroxto01Ox!ONEFFRE COOFodd.0000S000 - oxtFFE-- OH oxiFFE Oxt FFF FFE BFFTAOEFFECove<br>(6Bsaa SRAM) | Ox 1000 C000 . Byi000 FREE<br>[Reserved Jox0820 0000 . x0 FFF<br>| Fras [Reservedmemery || ox0800ox0020 0000 -x08F PY<br>mamaryarTinea Fas, yee 0000 - ono7FF FFP cone 0000<br>on he BOOTSSRabs depending ]®x0000 0000 OXOO1F FFFF<br><!-- End of picture text -->

##### **Memory map** 

**10** 

**ES, NLT 2026** 

# **<u>Important notices</u>** 

- ❑ High CPU clock rate: requires a software architecture to efficiently use the CPU’s capabilities 

l Polling in main loop l Interrupt handling l Interrupt-based and DMA for I/O l Task management with embedded OS 

→We’ll learn these things gradually 

- ❑ A lot of peripherals, each requires very complicated configuration: requires special design tools 

   - →STM32CubeIDE 

- ❑ A lot of CPUs from different vendors, but share the same Cortex-M cores: requires libs/middleware for scalability and reusing code. 

→ CMSIS, HAL, LL libraries... 

**11** 

**ES, NLT 2026** 

# **<u>STM32F429ZI MCU</u>** 

- ❑ Docs: 

l STM32F427xx STM32F429xx datasheet l STM32F Reference 

- ❑ STM32F429ZIT6 is a product in STM32F429 series l 180 MHz max CPU (4-26 MHz crystal) l 2 MB Flash, 256 KB + 4 KB SRAM 

   - l FPU + DSP core 

   - l Built-in Ethernet, USB 

   - l 17 Timers (16/32 bits, 180 MHz) 

   - l 3x12 bits ADCs (3x2.4 MSPS, 24 channels) 

   - l 21 communication interfaces (SPI, I2C, I2S…) 

   - l Camera interface, LCD interface, DRAM interface… 

   - l RTC, CRC, Random generator… 

   - l … 

**12** 

**ES, NLT 2026** 

# **<u>STM32F429ZI MCU: GPIO pins</u>** 

- ❑ LQFP144 package: 144 pins 

- ❑ GPIO ports: PA, PB, PC, PD, PE, PF, PG, PH 

- ❑ Each port has multiple pins, each pin can perform multiple functions 



<!-- Start of picture text -->
Figure 13. STM32F42x LOFP144 pinout<br>5 oe 2. sauce ueees<br>SRHERESEERREeSoe eeeREE SHEERS Reeeas<br>peed<br>PesgPedpes 23 eee eee eee eee a EERE NS Beet eee e eee 10Ny,107 ByeByes,4<br>Powdresvaste «768 403teejorws BtBeart Be atons<br>PoisePOL 10 jo2 arcoBeas<br>Pred1g tett =Sr Beer<br>Pred ie Fag<br>Pred ts Bye<br>perPredYostgi19is18 LorPiss 91sobee BeesBrarBeas<br>fag be] steed<br>Prior 2 sr heae<br>rae Bron<br>nord 2 2B Vee<br>roodng 27 bieErots<br>foodPC2d 28 81BaronsP01:<br>vend 31 Te fapbe<br>VendaVand BesBees<br>weg se 7s Bate<br>maid 3s Beats<br>pad 36 rapeste<br>BSSSTITTOSTSSSSADTRSGSRSSISSESEESAEK<br>ZHSILLISPRSST<br>SSSR ESTED ER EESAB arsesSEER ESROSee geersesSIC EEEEESEees AB5 sem<br><!-- End of picture text -->



<!-- Start of picture text -->
Table 10. STM32F427xx and STM32F429xx pin and ball definitions<br>2 eo | Pinname | & st<br>sia El/elsa}5a/S/e8] 2§ |cunctionareset) | & = Alternate functions |Additionalfunctions<br>8 g i<br>8 2/8/$|/s|e<br>3 = La<br>TRACECLK,<br>SPI6_SCK,<br>a2 1 FT SAI1_MCLK_A,<br>ETH_MIl_TXD3,<br>FMC_A23, EVENTOUT<br>TRACEDO,<br>2 ct cto] 2 FT| - |SAlt_SD_B,FMC_A19,<br>EVENTOUT<br>TRACEDI, SPI4_NSS,<br>3 | c2 3/81 rT SAI_FS_A,DCMI_D4, FMC_A20,LCD_80,<br>EVENTOUT<br><!-- End of picture text -->

_See Datasheet for other pins_ 

**13** 

**ES, NLT 2026** 

# **<u>STM32F429ZI: GPIP pins alternate functions</u>** 



<!-- Start of picture text -->
Table 12. STM32F427xx and STM32F429xx alternate function mapping<br>usartal | canta | oTG2_HS<br>UARTAISI7 |TIM12/13/14| IOTG1_ ragsore Leo<br>8 mcd FS s<br>TiN2,No | TINE USART2, ETH Ml EVEN<br>pat Tia, | TINS RX_CLKETHM EVEN<br>cH | cH THRMI_ TOUT<br>REF_CLR<br>Tina, | TINS USART2_ ETH EVEN<br>cHy | cH TK MDIG TOUT<br>jo] = [oeTivz_ |[oeTINS  feel] | [eee] | [ceeOTG_HS fee| | | [=|EVEN<br>wey pem_ | uco_ | even<br>2s ws HSYNC | vSYNC | TouT<br>TIN2,Me tive, oTG_HS EVEN<br>Tim | Tiva_ | tive. EVEN<br>PAT timcHIN || Tiva_CHE | Time.CHIN TIMI4_CHI ETHRMIIETHRXVMi TOUTEVEN<br>_CRS_DV<br>a TIM O16 FS, EVEN<br>TMi_ USARTI_ Domi EVEN<br>CHE TK Do TOUT<br>TIM OTG_FS_ EVEN<br>CHS 1D TOUT<br>eeTitTIM USART! O76 FS, eeEVEN<br>eoaO76 FS, EVEN<br><!-- End of picture text -->

_See Datasheet for other ports_ 

**14** 

**ES, NLT 2026** 

# **<u>Exercise: STM32F429ZIT6</u>** 

- ❑ Get the below info from STM32F429ZIT6 datasheet 

   - l How many GPIO ports are available? 

   - l How many pins are available on each port? 

   - l What is the normal operating voltage of the MCU? 

**15** 

**ES, NLT 2026** 

# **<u>STM32F429I-DISCOVERY development kit</u>** 

- ❑ STM32F429ZIT6 ARM Cortex-M4 

- ❑ 2 MB flash, 256 KB SRAM 

- ❑ 8MB SDRAM 

- ❑ On-board ST-Link debugger 

- ❑ 2.4” QVGA touch LCD 

- ❑ 6 LEDs (2 user LEDs) 

- ❑ 3 axis gyros 

- ❑ … 



<!-- Start of picture text -->
{se PS: ee Faery Hi<br>ig ed nent Wold =<br>ae see baetgt Fa owe -<br>ae a eet > oes ‘.<br>~ eeales a =O werorse<br>Ww m32f4-disco== cea<br>b<br>ie f jaa meee! eee waitin<br>so]Fattga)<< ||P7 cea, iis)<br>ee<br>thy = Nee etre can<br>ea<br>ol Ee pe cee<br>rioottihronioois$hh =owes,+ 1) LaPt Sheae<br>rs ioe!3 3 L¢ ie<br>Isl<br>ieonl 6] ns ‘g@ino<br>a=ioe! ee em<br>m & ©! iy eire<br>Jeoore:rm 10 ©} iad<br>mm ioe! Re<br>risie ©: RSise<br>flo!111enda}ioe!© { anejoejmnsose<br>rm Sie<br>lee!<br>iarm ere! neinia @jrao<br>rule €; jogs<br>ol sei@: | Deira<br>rasieoe! oe<br>mui nae<br>m5ive! inane<br>mo iwe! }D.@j ros<br>ms ie @jrowe<br>“8 om<br>ra joe: isieimes<br>7071 10fos! 1@.@! Nelhatf€} | iaons @jra<br>“ved —<br>casa3se a =<br>s<br><!-- End of picture text -->

**16** 

**ES, NLT 2026** 

# **<u>STM32F429I-DISCOVERY development kit</u>** 

# ❑ Hardware overview 



<!-- Start of picture text -->
Figure 2. Hardware block diagram<br>Mini USB<br>Embedded<br>ST-LINK/V2-B<br>fa}=b<br>ofed<br>STM32F429ZIT6<br>2 5<br>s3<br>8RESET g<br>x=<br>LEDs<br>LD3...LD6 RESETB2<br>SDRAM Bi<br>64 Mbits USER<br>2.4" QVGA 13G4250D<br>TFT LCD<br>MSv32376V3<br><!-- End of picture text -->

**17** 

**ES, NLT 2026** 

# **<u>STM32F429I-DISCOVERY development kit</u>** ❑ Hardware overview 



<!-- Start of picture text -->
Figure 3. Top layout<br>pees<br>I peesA  eex see ee,<br>ST-LINK/V2-B i Lp2<br>Lot |<br>COM (red/green LED) a eed oo rm | PWR ite(red LED ,<br>om2 cote: oerGR, ESS” ky leBe | |<br>CN2 oes acme): 7 Be |<br>SWD connector” | s[i] Bion,Sue fo) 0009,608-5opine 5,  “E = ||<br>JP3__ 1 | Sele ‘lela: ia nia !<br>Ipp measurement ; ” be ‘eingoBegvor "@ 2x| De MEe175 |H enaST-LINK/DISCOVERY selector<br>Ld on www.st.com/stm32f4-discovery_<br>B1 ___| _!<br>user button mel a]O08 Re mles | 3 V power supply input/output<br>LD3 soa pe tm B2<br>(orange LED) ses 535ats =f]idem. =wt\ab oeen resetSB1  button<br>(green LED)Lb4 T bl ,CEED)_ “= 1@[Sel @}rn0 (B2 - RESET)<br>}@ Olona<br>2.4" TFT LCD cose e soln.<br>Pat }@ @lrcs<br>Pais] }@ @}rs0<br>roxG13) ll 1@Jo or:Olrsz<br>69 }@ Orns<br>07 }@ @lrris<br>POs, 1@ Orci<br>os }@ Orcs<br>poL }@ @}rcio<br>pcaa| }@ @lrciz<br>Pc10| ssiPena<br>ber LCD 2.4" loam:<br>Pato] }@ @}ross<br>Pas, }@ @}roe<br>pce |@ @}ro10<br>POS }@ @}roiz<br>G7 }@ @}roie<br>Pcs }@ @}rcz<br>exo Lo xo<br>sau jj<br><!-- End of picture text -->

**18** 

**ES, NLT 2026** 

# **<u>STM32F429I-DISCOVERY development kit</u>** 

# ❑ Hardware overview 



<!-- Start of picture text -->
Figure 4. Bottom layout<br>a ee J<br>SB3, SBS, SB7, SB13 e $B12 (NRST)<br>SB4, SB6,(RESERVED) SB8, SB14 | SETI RXNT,<br>(DEFAULT) ' a e at |aa $B10 (STM_RST)<br>~ ‘s ‘SB9 (SWO)<br>OTe meea SB15 (RX, TX)<br>SB19, SB20 a om<br>(X3 crystal) ee e SB16, SB17<br>ee ee (X2 crystal)<br>oo Sas ott ee<br>oo. als nee<br>oor s mi mmg) § #/ 8 cme e<br>\oopi a am - ee<br>SB18 eoe°, ma f atattines 0°eo<br>(MCO) |r leer: ii E'S $<br>e oo | He Booseymary) 821(B00T1)<br>eo = lee<br>STM32F429ZIT6U5 eo3. Ue iHed ty ee— SB22, SB23, SB24, SB25<br>SSee  | seth. amy falecp.tiss<br>eet ay eke [tes<br>So<br>ees = mito‘ © Greeee<br>SB26, SB27 eo"J g iv—— ee) SDRAM<br>(USB OTG) oo > vhutemiminionm CC * ee<br>ak a alae<br>3eee “S18senna aE 05 iseee<br>ear td Wye ouves joe CNG<br>fee os Domi USB OTG Micro-AB<br><!-- End of picture text -->

**19** 

**ES, NLT 2026** 

# **<u>STM32F429I-DISCOVERY development kit</u>** 

# ❑ Pin mapping 



<!-- Start of picture text -->
Table 7. STM32 pin description versus board functions<br>g | E r/o ]e x|z}o FB<br>ee /el(slele lle al2i/#|)2)eleiziele<br>= & & > 8 8 8 4 g 3 2 3 S/o]6<br>e<br>BOOTO |138 8 21<br>a<br>5<br>é elele<br>pee bs UBL TATGo) | o del tL dst ppl<br>Cceee<br>po be ETT PP PEE TTT P Ef fT fe<br>po |-f-fefete] | fff [ff] [fff]<br>|><br>ee feEEEo]o> EEE ELLE EET<br>cS Oe<br>feels eeeeeeeeen<br>bE<br>PAT 43 v4 4 23<br>oatg<br><!-- End of picture text -->

**20** 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

- ❑ See the kit’s User manual and Schematics to find the below info: 

   - l How are LEDs LD1 – LD4 controlled? When are they turned on/off? 

   - l Which pins on STM32F429 are connected to B1 và B2 buttons? What are the functions of these buttons? How do they work? 

   - l Which pins on the P1 and P2 extension headers are connected to the Touch Panel? 

   - l Which pins on the P1 and P2 extension headers are connected to the gyroscope I3G4250D? 

   - l Which pins on the P1 and P2 extension headers are not connected to any peripherals on the board? 

**21** 

**ES, NLT 2026** 

# **<u>LD1 – LD4 LEDs</u>** 



<!-- Start of picture text -->
Idd<br>3V JP3 VDD<br>4<br>K<br>LD2 HW3<br>FLED,x  red<br><!-- End of picture text -->



<!-- Start of picture text -->
LD1<br>con 2 af y<br>100<br>KK<br>uep_stunk | R13 a 4B be<br>io | 7<br>[D_BICOLOR_CMS<br><!-- End of picture text -->



<!-- Start of picture text -->
LD3<br>(rea es Si,ng Green 4bl?<br>510<br>LD4<br>Red<br>(ra Pet 5,16805, bl 2 —<br>LEDs<br><!-- End of picture text -->

**22** 

**ES, NLT 2026** 

# **<u>Push buttons</u>** 



<!-- Start of picture text -->
VDD<br>R25 r ) Not Fitted VDD<br>g HW6 ag, SRO<br>cu 22 100K.<br>100nF sw 5s& (axsr}“8<br>(emp<br>sd sB2 ts‘wo “"q g= 8<br>Ee c12 22 uw<br>E<br>USER RO? ol £<br>& WAKE-UP utBu t t on 220K RESETButton ey Q:<br>of F<br>=<br>co}<br>= &<br><!-- End of picture text -->

**23** 

**ES, NLT 2026** 

# **<u>General Purpose Input/Output</u>** 

- ❑ GPIO is the most basic peripherals of MCUs. 

- ❑ GIOP pins (chân vào ra) are digital signal pins that supports input and output. 

   - l Input: receive signals from buttons, switches, sensors… 

   - l Output: send signals to drive LEDs, or to control other ICs/devices. 

   - l Logical values 0 and 1 correspond to low and high voltage signals. 

- ❑ GPIO ports: groups of multiple pins (normally 8 to 16). 

- ❑ GPIO pins can be multiplexed with other alternative functions (communications, analog signal,…). 

**24** 

**ES, NLT 2026** 

# **<u>General Purpose Input/Output</u>** 

# ❑ GPIO pin modes 



<!-- Start of picture text -->
e Input floating<br>e —_ Input pull-up<br>e —_Input-pull-down<br>e = Analog<br>e Output open-drain with pull-up or pull-down capability<br>e Output push-pull with pull-up or pull-down capability<br>e = Alternate function push-pull with pull-up or pull-down capability<br>e Alternate function open-drain with pull-up or pull-down capability<br><!-- End of picture text -->

**25** 

**ES, NLT 2026** 

# **<u>GPIO pin structures</u>** 

# ❑ Source: STM32F429 reference 



<!-- Start of picture text -->
Figure 25. Basic structure of a five-volt tolerant I/O port bit<br>rT TTT TTT TTT<br>To on-chip Analog | |<br>peripheral | |<br>Alternate function input<br>®D<br>. | on/off |<br>Read 2<br>2 Ey3&s | TTL. Schmitt<y | Yoo Yoo_er”Protection<br>2 3 | trigger onoft | Pull L\ diode<br>Write SSF 5 £ cinputdriver. up [|V0 pin<br>£/] | i ae re<br>3 £ | ono! | pull “Protection<br>= 3 pow" | diode<br>a 3 | P-MOS | v.<br>3 Output SS Vgg<br>. s | control |<br>Read/write fo} N-MOS<br>From on-chip . Vss Push-pull<br>peripheral Alternate function output open-drain or |<br>. be ~~ ~ ~ _adisabled_ 4 Analog<br>ai15939b<br><!-- End of picture text -->

**26** 

**ES, NLT 2026** 

# **<u>GPIO pin structures</u>** 

# ❑ Working modes 



<!-- Start of picture text -->
Figure 29. Output configuration<br>posta<br>s| ! on i<br>Read aL!2 I<br>® a]a] |y TTL Schmit I\ Vop vYoo<br>3 Es ‘wager oniof]<br>£ 5 Input driver diode<br>3 5 ulmput driver ul<br>el (23 "apt—  averee Yoo al us i108in<br>Es a | l A<br>5 | dLewos | pu ZNorrecton<br>3 Output jgown | diode<br>geRe a d/wtu ri tete__ 6 1 control NMOS | Ys yss<br>| yt Push of<br>bo eSeran aitsoa1b<br><!-- End of picture text -->



<!-- Start of picture text -->
Figure 28. Input floating/pull up/pull down configurations<br>po-----------5<br>I I<br>x]— | on ]<br>Read g sa] 1 <I | Vpp YoD<br>g<br>Write e £ put 4 diode<br>3 5 i l pat<br>el] z|2 cneutdiver— DDD DDD II) free Cv08VO pin<br>EaRRES pmnaer 7 Hou Z\ protection<br>als | |) Spam] Boe<br>3 | |v<br>Readhrite 3 1 | ‘SS Vss<br>| |<br>ne) aneeioe<br><!-- End of picture text -->



<!-- Start of picture text -->
Figure 30. Alternate function configuration<br>Toon-chip roscoe 4<br>meripheral Alternate function:  iput__|\ \1<br>Read FI \ ” |<br>2 3ge Hl TTL Schmit<<] |JonoVop \, Yoo<br>3 Ez \ tigger | Buds protectionSoe<br>write | 2 & cinputdiveroodG ad 0<br>nls VO pin<br>3 "omput ver Yoo “ono<br>e2| Wg5 I {_P-vos Ia nA tecion<br>= | Output ig diode<br>Faz | control | Vs viMes<br>Roadie | 8 Naos<br>| ver pusmpuitor |<br>From on-chip Lf— — — — — — “8 _eren-rain 4<br>peripheral ‘Alternate function output aits9420<br><!-- End of picture text -->



<!-- Start of picture text -->
Figure 31. High impedance-analog configuration<br>oe<br>Toon-chip <A og r aT!<br>peripheral | |<br>Read 3A? || 5 off ||<br>¢ 88 <| “eo<br>2 2 I TTL Schmitt I<br>o = trigger protection<br>wie} 2] | ! a ote<br>FaS113s Linput driver Lv pin<br>3 2<br>az g3 |p-------4| LX protection<br>z diode<br>3 I \<br>Readhwrite é 1 1 Ves<br>I I<br>From on-chip Analog bo-— ~~~ --|-~-4<br>peripheral sinsoas<br><!-- End of picture text -->

_Nếu_ **_đọc_** _vào từ một_ **_output GPIO pin_** _thì sao? Nếu_ **_ghi_** _ra một_ **_input GPIO pin_** _thì sao?_ 

**27** 

**ES, NLT 2026** 

# **<u>Programming with GPIO</u>** 

- ❑ Each GPIO port is controlled by a number of 32 bit registers 

l 4 configuration registers: set working mode for each GPIO pin 

   - GPIOx_MODER, 

   - GPIOx_OTYPER, 

   - GPIOx_OSPEEDR, 

   - GPIOx_PUPDR 

- l 2 data registers: hold the read/write buffers of each pin 

   - GPIOx_IDR, 

   - GPIOx_ODR 

- l Set/reset register: GPIOx_BSRR 

- l Locking register: GPIOx_LCKR 

- l 2 alternate function selection registers 

   - GPIOx_AFRH, 

   - GPIOx_AFRL 

**28** 

**ES, NLT 2026** 

# **<u>Example: Port bit configuration</u>** 

# ❑ See Reference for more details about each register 



<!-- Start of picture text -->
Table 36. Port bit configuration table)<br>aarti OTYPER(i) Osea eo 1/0 configuration<br>(BA jo fo [oPoutpt foo<br><!-- End of picture text -->

**29** 

**ES, NLT 2026** 

# **<u>Programming with GPIO</u>** 

# ❑ GPIO ports can be controlled directly by read/write the port registers. 

l ➔Very very difficult task to comprehend all these configuration registers. 

# ❑ GPIO drivers 

- l HAL (Hardware Abstraction Layer): high-level and featureoriented APIs with a high-portability level, hides the MCU and peripheral complexity from the end-user. 

- l LL (Low-level) drivers offers low-level APIs at register level, with better optimization but less portability, require deep knowledge of the MCU and peripheral specifications. 

**30** 

**ES, NLT 2026** 

# **<u>Programming with GPIO</u>** 

# ❑ HAL_GPIO functions 



<!-- Start of picture text -->
Initialization and de-initialization functions<br>This section provides functions allowing to initialize and de-initialize the GPIOs to be ready for use.<br>This section contains the following APIs:<br>. HAL_GPIO_Init()<br>. HAL_GPIO_DelInit()<br>10 operation functions<br>This section contains the following APIs:<br>. HAL_GPIO_ReadPin()<br>. HAL_GPIO_WritePin()<br>. HAL_GPIO_TogglePin()<br>. HAL_GPIO_LockPin()<br>. HAL_GPIO_EXTI_IRQHandler()<br>: HAL_GPIO_EXTI_Callback()<br><!-- End of picture text -->

**31** 

**ES, NLT 2026** 

# **<u>Programming with GPIO</u>** 

# ❑ LL_GPIO functions 



<!-- Start of picture text -->
# LL_GPIO_ReadReg()<br>©* LL_GPIO_SetPinMode(GPIO_TypeDef*, uint32_t, uint32_t) : void<br>°° LL_GPIO_GetPinMode(GPIO_TypeDef*, uint32_t) : uint32_t<br>e* LL_GPIO_SetPinOutputType(GPIO_TypeDef*, uint32_t, uint32_t) : void<br>©° LL_GPIO_GetPinOutputType(GPIO_TypeDef*, uint32_t) : uint32_t<br>e* LL_GPIO_SetPinSpeed(GPIO_TypeDef*, uint32_t, uint32_t) : void<br>©* LL_GPIO_GetPinSpeed(GPIO_TypeDef*, uint32_t) : uint32_t<br>©° LL_GPIO_SetPinPull(GPIO_TypeDef*, uint32_t, uint32_t) : void<br>©* LL_GPIO_GetPinPull(GPIO_TypeDef*, uint32_t) : uint32_t<br>©° LL_GPIO_SetAFPin_0_7(GPIO_TypeDef*, uint32_t, uint32_t) : void<br>©° LL_GPIO_GetAFPin_0_7(GPIO_TypeDef*, uint32_t) : uint32_t<br>© LL_GPIO_SetAFPin_8_15(GPIO_TypeDef*, uint32_t, uint32_t) : void<br>°° LL_GPIO_GetAFPin_8_15(GPIO_TypeDef*, uint32_t) : uint32_t<br>© LL_GPIO_LockPin(GPIO_TypeDef*, uint32_t) :void<br>©° LL_GPIO_IsPinLocked(GPIO_TypeDef*, uint32_t) : uint32_t<br>e* LL_GPIO_IsAnyPinLocked(GPIO_TypeDef*) : uint32_t<br>©° LL GPIO_ReadInputPort(GPIO_TypeDef*) : uint32_t<br>©° LL_GPIO_IsInputPinSet(GPIO_TypeDef*, uint32_t) : uint32_t<br>©* LL GPIO_WriteOutputPort(GPIO_TypeDef*, uint32_t) : void<br>©° LL_GPIO_ReadOutputPort(GPIO_TypeDef*) : uint32_t<br>e* LL_GPIO_IsOutputPinSet(GPIO_TypeDef*, uint32_t) : uint32_t<br>©* LL_GPIO_SetOutputPin(GPIO_TypeDef*, uint32_t) : void<br>©° LL_GPIO_ResetOutputPin(GPIO_TypeDef*, uint32_t) : void<br>©* LL_GPIO_TogglePin(GPIO_TypeDef*, uint32_t) : void<br><!-- End of picture text -->

**32** 

**ES, NLT 2026** 

# **<u>Tool chain</u>** 

❑ STM32CubeIDE: IDE + compiler + debugger 

❑ STM32CubeF4: driver + library (install inside CubeIDE) 

❑ ST-LINK009: USB driver (bundled with CubeIDE) 

**33** 

**ES, NLT 2026** 

**<u>Code example 1: Hello World</u>** 

❑ Objective: 

l Create the first project for STM32F4 from scratch l Configure GPIO to control an LED with HAL functions 

**34** 

**ES, NLT 2026** 

# **<u>Create a new project</u>** 

# ❑ Menu File → New → STM32 Project → MCU/MPU Selector 

## l Search for STM32F429ZIT6 from part number box 



<!-- Start of picture text -->
|| Target(i st22 SelectionProject o DEx |<br>Select STM32 target or STM32Cube example ,<br>|<br>| MCU/MPU-MCU/MPU SelectorFilters Board Selector Example Selector Cross Selector |<br>* Fea) kz O (Fn) Block... [Docs& Res. capre.. [E]oa.. [4G ||<br>CommercialPort Number ‘STM32F429Z1T6 v ___ STMS2F4 Series<br>ty<br>6 High-performance i]<br>“ . BS advanced line, Arm Cortex-<br>a)= nee eee<br>PRODUCT INFO M4 core with DSP and FPU,<br>Segment G MCUs/MPUs List: 2 items «fy Export<br>cos S L Part No Refere.. Mark... Unit... Board Pack... Flash RAM Comm...<br>Line QE sTMa2. STM32... Active 7.6662 ININ... ST._|LOFPST 1... 2048 k... 256 kBy...STM32.<br>- jsTm32... [Active [7.6662 [LQFP 1... |2048 k... [256 kBy..{STM32...<br>Marketing Status Q<br>@ Kk Next > Finish Cancel<br><!-- End of picture text -->

**35** 

**ES, NLT 2026** 

# **<u>Create a new project</u>** 

# ❑ Set project name, firmware package V1.28.0 or V1.28.1 l Project path must not contain space or special characters 



<!-- Start of picture text -->
(B stm22 Project a x<br>(0)=)<br>Setup STM32 project<br>Project<br>Project Name: HelloSTM32|<br>Use default location<br>laesitten C:/Users/ngola/STM32CubelDE/workspace_1.6.1 Browse.<br>Options<br>ed<br>egeelleress<br>Oc Oc+<br>Targeted Binary Type<br>O Executable O Static Library<br>Targeted Project Type<br>O sTM32Cube © Empty<br>® <Back Next > Cancel<br><!-- End of picture text -->



<!-- Start of picture text -->
(B stm32 Project a x<br>Firmware Library Package Setup IDE<br>Setup STM32 target's firmware<br>Target and Firmware Package<br>Target Reference: STM32F4291-DISC1<br>Firmware Package Name and Version: STM32Cube FW.F4 1.27.0<br>Firmware and Software Package Repository<br>Location:<br>A\Users\ngola\STM32Cube\Repository<br>See ‘Firmware Updater’ for settings related to package installation<br>Code Generator Options<br>Odd necessary library files as reference in the toolchain project configuration file<br>Copy all used libraries into the project folder<br>© Copy only the necessary library files<br>@ — <Back Next> Cancel<br><!-- End of picture text -->

**36** 

**ES, NLT 2026** 

# **<u>Configure GPIO</u>** 

❑ PG13 and PG14 are connected to LED3 and LED4 → need to configure them as output 

❑ Select System Core → GPIO: l Set PG13, PG14 to GPIO_Output 

❑ Ctrl+S → save *.ioc file and auto-generate code 

**37** 

**ES, NLT 2026** 

# **<u>Configure GPIO</u>** 

# ❑ PG13 and PG14 as Output, push-pull, Low 



<!-- Start of picture text -->
Pinout & Configuration Clock Configuration Project Manager Tools<br>~ Software Packs ~ Pinout<br>| | & GPIO Mode and Configuration N ‘OF Pinout view #** System view<br>: |<br>system Core a) Group By Peripherals L<br>x © cr10<br>DNA<br>WO6 Search Signals<br>vic Search (COHF) O Show<br>only Modified Pins BE<br>Rec [ee §§<br>sis Pin W.. Sigh... GPIO... GPIO... GPIO... Maxi.. User. Modi. 8S<br>wwos Po13012 f|nf a __ it[L ow —_Outbut.._(Output...No pull..|LoNo pull..Lo w ie)o alelelal EARREEER zie= A elelelalalal lalelalalalalal<br>PDi4— n/a Low (Output... |No pull... Low: {a}<br>Analog ©) 015 _nfa_—Low_Output... No pull... Low (a)<br>PG2 ina Low (Output... No pull... |Low is}<br>PGi4—ona Low Output... |No pull... Low: {=}<br>Connectivity © G13 Configuration =<br>— 9 GPI0 outputevel Low g<br>aa SC P10 mode ‘Output Push Pull g<br>a Sy 6010 Pul-up/Pull-down No pull-up and no pulldown v Q~ bk. dad tH -FQ<br>thee nese. Packs Maximum output speed Lots ~ —___——<br><!-- End of picture text -->

**38** 

**ES, NLT 2026** 

# **<u>Source code for main()</u>** 

```
/* Reset of all peripherals, Initializes the Flash
interface and the Systick. */
```

```
HAL_Init();
```

```
/* Initialize all configured peripherals */
```

```
MX_GPIO_Init();
```

`/* Write 1 to GPIO` → `turn LED ON */` 

```
HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13|GPIO_PIN_14,
GPIO_PIN_SET);
```

**39** 

**ES, NLT 2026** 

# **<u>Build, download, and run</u>** 

❑ Run --> Run as STM32 CortexM C/C++ Application ❑ Plug board to PC’s USB port using the mini USB cable. ❑ Select Debugger as SWD, then Apply and Run l If more than one board is connected, select the correct S/N 



<!-- Start of picture text -->
(Di Run Configurations o x<br>Create, manage, and run configurations @<br>a Name: |CubelDE<br>‘ypeBCIC+ fiter textApplication 1B Main \ % Debugger|. > Startup| Source Common<br>TICIC++ Remote Application | C/C** Application:<br>f> LaunchLaunch Group Group (Deprecated) Project:Debug\CubelDE elf Search Project.- Browse..<br>¥ ISTM32 Cortex-M C/C++ Applic<br>Ci CubelDE CubelDE‘ube Browse.=<br>Paint Build (if required) before launching<br>Build Configuration: Select Automatically ¥<br>O Enable auto build Disable auto build<br>OneIse workspace—— stingsettings : ‘onfigureos eeeWorkspace ewSettings.<br>< ><br>Filter matched 7 of7 items fered Apply<br><!-- End of picture text -->



<!-- Start of picture text -->
[Di Run Configurations o x<br>Create, manage, and run configurations (>)<br>aaa ‘Name: [CubelDE<br>Sype FiteEICIC++BCIC++ tertApplicationRemote Application |B@iea Main|® pines Debugger \“ Startup] Source = Common a<br>‘@ Launch Group © Autostart local GDB server Host name or IP address. localhost<br>> Launch Group (Deprecated) O Connect to remote GDB server Port number 61234<br>¥ STMB2 Cortex-M C/C++ Applic:<br>i CubelDE Debugoe probe ST-LINK STANK(ST-LINKGDB server).J<br>Paint GDB Server Command Line Options<br>Interface<br>ou) Onis<br>MAst-uinksn [0660FF545052636687114315 __~| Scan<br>Frequency (kHa:|Autlo<br>Accesspor: [0-CoterMs<br>Reset behaviour<br>Type: Connect under reset<br>Serial Wire Viewer (SWV)<br>< > [Enable a<br>Fiter matched 7 of 7 items oe Apply<br><!-- End of picture text -->

**40** 

**ES, NLT 2026** 

# **<u>Analyze the project structure and files</u>** 

# ❑ Code files: *.c, *.h, *.s 

❑ Drivers 

# ❑ **To-do** : do the same thing (turn on LEDs) but using LL functions instead of HAL functions. 



<!-- Start of picture text -->
Pinout & Configuration} Clock Configuration Project Manager Tools<br>Driver Selector Register CallBack<br>Project ‘ * \ .<br>RCC HAL ADC DISABLE<br>GPIO LL ¥ CAN DISABLE<br>Code Generator Le ceECcRYP DISABLEDISABLE<br>DAC DISABLE<br>Demi DISABLE<br>prsoM DISABLE<br>Generated Function Calls DMA2D DISABLE<br>psi DISABLE<br>. Syste... RCC o o HASH DISABLE<br>77 MX.G.- ePIO o HCD DISABLE<br>lac DISABLE<br>FMPI2c DISABLE<br>12s DISABLE<br>IRDA DISABLE<br>LPTIM DISABLE<br><!-- End of picture text -->

**41** 

**ES, NLT 2026** 

# **<u>Exercise: LED blinking</u>** 

❑ Objective: 

l Develop from previous example code. l Turn on/off LEDs periodically 

**42** 

**ES, NLT 2026** 

# **<u>Source code for main loop</u>** 

### **`while (1)`** 

```
  {
```

```
HAL_Delay(500);
```

```
HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
HAL_Delay(500);
```

```
HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
```

```
  }
```

**Note: the above code can be simplified a bit by using HAL_GPIO_TogglePin()** 

**43** 

**ES, NLT 2026** 

# **<u>Exercise: Interfacing LED with GPIO</u>** 

- ❑ Assemble the below circuit on breadboard. 

   - l Select suitable pins on the extension header P1, P2. 

   - l Connect selected pins with the LED ( **don’t forget the 330 ohm** resistors). 

- ❑ Write code to blink the 2 LEDs with different frequencies. l Configure GPIOs 

   - l Write code in main loop. 



<!-- Start of picture text -->
ol<br>1 2<br>ol<br>1 2<br><!-- End of picture text -->

**44** 

**ES, NLT 2026** 

# **<u>Exercise: Input with GPIO</u>** 

- ❑ Update the above project so that: 

   - l The LEDs blinks only when the Blue button is pressed. l The LEDs are permanently ON when the Blue button is released. 

**45** 

**ES, NLT 2026** 

# **<u>Exercise 2: 7 segments LED interfacing</u>** 

# ❑ 5161AS module (common-cathode) 



<!-- Start of picture text -->
gS<br>ae 1,35<br>a || J | slp—A<br>ay= BPI—fe0<br>Rt b bP<br>ott Yong<br><!-- End of picture text -->



<!-- Start of picture text -->
3,8<br>Al B] C} D} BE] F} Gop<br>764219 105<br><!-- End of picture text -->



<!-- Start of picture text -->
Ri<br>[LL ED_ AA> [Ri } [> 7<br>[LeD_8»>LED_B [R2] > BE<br>[ LED _C_c» [ R 2 S ] "2bPing<br>pe<br>[LL ED_ EE» [RS] > DA<br>R5 95 1<br>$$ p~ ono<br>[ LED _G_¢» [ R 7T] >P577<br>cm =fD8<br><!-- End of picture text -->

**46** 

**ES, NLT 2026** 

# **<u>Exercise 2: 7 segments LED interfacing</u>** 

❑ Build a circuit for controlling a 7-seg LED module based on the following schematic. 

l GPIO pins for LED_A to LED_P can be selected from the free STM32F429 pins on headers P1 and P2. 

- ❑ Write a program to display the digits 0 to 9 sequentially. 



<!-- Start of picture text -->
UL<br>5161AS<br>LED_8LER 30a 559 68fe Le<br>ae<br>LED)pLeD_£530 30 > | ao<br>eS, oh<br>DP CC<br>HLED.G) ‘sso [7 se, CCT<br>7<br>GND<br><!-- End of picture text -->

**47** 

**ES, NLT 2026** 

# **<u>Exercise 3: 7 segments LED array interfacing</u>** 

- ❑ To display multi-digit numbers: use an array of multiple 7- seg LEDs. 

l Each 7-seg LED requires 8 GPIO pins. How about an array of 10? l Need to reduce the number of GPIO pins to control the 7-seg LED array. 

❑ Principal: LED scanning 

l Hardware: 

   - All 7-seg modules share the same data bus to control LED segments. 

   - Each module have a separate control signal to turn on/off the whole module. 

- l Software: LED scanning process 

   - Turn on one module at a time for a short time, then sequentially move to the next module in the array. 

   - Display the corresponding digit on each module when it is turned on. 

   - Repeat the above process indefinitely with a “suitable” frequency and delay time, the “retinal persistence” effect will cause the illusion as if all modules are turned on simultaneously. 

**48** 

**ES, NLT 2026** 

# **<u>Exercise 3: 7 segments LED array interfacing</u>** 

# ❑ Turn on/off LEDs with NPN transistor 



<!-- Start of picture text -->
COLLECTOR<br>1<br>2<br>BASE<br>3<br>EMITTER<br><!-- End of picture text -->



<!-- Start of picture text -->
v2<br>5V<br>D1 Y7<br>. ~«<br>LTL-307EE ‘X<br>RI<br>1509<br>2N2222<br>GC :<br>7 A. 18ko 7<br><!-- End of picture text -->



<!-- Start of picture text -->
TO-92<br>CASE 29<br>STYLE 17<br>15 1g<br>3 3<br>STRAIGHT LEAD BENT LEAD<br>BULK PACK TAPE & REEL<br>AMMO PACK<br><!-- End of picture text -->

**49** 

**ES, NLT 2026** 

# **<u>Exercise 3: 7 segments LED array interfacing</u>** 

❑ Reference schematic to drive two 7-seg LEDs is below. 

- ❑ Select the suitable GPIO pins to drive each segment, and to control the two 7-seg modules. 

- ❑ Configure the selected GPIO pins and write code to display the counting values from 00 to 99 on the two modules. 



<!-- Start of picture text -->
COLLECTOR<br>1<br>2<br>BASE<br>eure3<br><!-- End of picture text -->



<!-- Start of picture text -->
TO-92<br>CASE 29<br>STYLE 17<br>1 23 2 3<br>‘STRAIGHT LEAD BENT LEAD<br>BULK PACK TAPE & REEL<br>AMMO PACK<br><!-- End of picture text -->



<!-- Start of picture text -->
us<br>516145 SL61AS<br>TeDA #2?330 1aa éls1 iy<br>Hepesiossoeee. Ft aavat<br>Se ees<br>i Slop ect S\pp ech<br>f ? YP» a2<br>CoE’)&* tem— 2)&,<br>L Lt<br>GND ‘GND<br><!-- End of picture text -->

**50** 

**ES, NLT 2026** 



<!-- Start of picture text -->
TO-92<br>CASE 29<br>STYLE 17<br>1 i<br>3 3<br>STRAIGHT LEAD BENT LEAD<br>BULK PACK TAPE & REEL<br>AMMO PACK<br><!-- End of picture text -->



<!-- Start of picture text -->
COLLECTOR<br>1<br>2<br>BASE<br>3<br>EMITTER<br><!-- End of picture text -->



<!-- Start of picture text -->
, U3<br>sls 5161AS<br>— 330 alll, 1,<br>- -<br>—— p<br>ens{soIS, Cae 6 ecffe<br>Vv s<br>GND GND<br><!-- End of picture text -->

**51** 

**ES, NLT 2026** 

# **<u>Interrupt handling</u>** 

- ❑ Interrupt: very important activity, triggers the execution of a specific handler (code) on CPU when a specific event occurs. 

- ❑ Event: similar to interrupt, but it signals a peripheral to do a hardware function instead of code execution on CPU. 

- ❑ STM32F4 has a lot of interrupts/events, managed by the NVIC 

   - l GPIO, peripherals (timers, ADC, DAC,…) 

   - l SysTick, NMI. 

   - l 91 programmable interrupts, 16 priority levels 



<!-- Start of picture text -->
Microcontroller<br>Peripheral Cortex-M processor<br>| NMI (—) ProcessorCore<br>, re i NVIC<br>Peripherals ||[7 7<br>fF> tras kK — system<br>Ly [¢| Exceptions<br><<} 0 port<br>SysTick timer<br><< WO port<br><!-- End of picture text -->

**52** 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

❑ Table 63. Vector table for STM32F42xxx “RM0090 Reference”: list all interrupts that are supported by STM32F429. 

❑ How are they supported by software? 

**53** 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

- ❑ What is the external interrupts EXTIs? 

- ❑ How many external interrupts can work simultaneously? 

- ❑ See page 383 “RM0090 Reference” and describe how to set up the configurations for an external interrupt. 

**54** 

**ES, NLT 2026** 

# **<u>Exercise 4: Handing external interrupt</u>** 

- ❑ Set up the external interrupt corresponding to the PA0 pin and handle that interrupt event in software the Green and Red LEDs are toggled when the Blue button is pressed. 

❑ Set up mode for PA0 as GPIO_EXTI0 

l Set working mode: External Interrupt Mode with Rising edge 

- ❑ Enable the interrupt handler in NVIC 

- ❑ Write code for the interrupt handler in *_it.c 

```
voidEXTI0_IRQHandler(void)
```

**55** 

**ES, NLT 2026** 

# **<u>Exercise 4: Handing external interrupt</u>** 

# ❑ Set up GPIO configuration for PA0, PG13, PG14 



<!-- Start of picture text -->
VOD.<br>|VREF+<br>GPIO_ExTIO |e<br>[pI TIM8_ETR.<br>[PI USART2_CTS.UART4_TX<br>GPIO_Input<br>GPIO_Output<br>GPIO_Analog |B ]<br>evENToUT<br><!-- End of picture text -->



<!-- Start of picture text -->
ee<br>{0} Pinout view = system view<br>B32£8<br>2 2<br>Oo2 Oo2<br>|<br><9 O}) ol =<br>S| 2] S| SIRENS 2 &<br><!-- End of picture text -->

Computing **ES, NLT 2026** 

**56** 

# **<u>Exercise 4: Handing external interrupt</u>** 

# ❑ Write code for the EXTI0_IRQHandler() function 

# ❑ How it works: 

- l `MX_GPIO_Init` : set up PA0 with rising edge detection. 

- l **`EXTI0_IRQHandler`** : the routine to be called automatically when the EXIT0 interrupt is raised, corresponding to when the button is pressed down. 



<!-- Start of picture text -->
[Qmainc @ *stm32f4xx_itc x [B startup_stm32f429zitxs<br>ZUS “/<br>204-void EXTIO_ IRQHandler (void)<br>205 {<br>206 /* USER CODE BEGIN EXTIO IRQn 0 */<br>207<br>208 /* USER CODE END EXTIO TRQn 0 */<br>209 HAL GPIOEXTI_IRQHandler(GPIO PIN 0);<br>210 /* USER CODE BEGIN EXTIO IRQn 1 */<br>211<br>212 /* USER CODE END EXTIO TRQn 1 */<br>213 }<br><!-- End of picture text -->

**57** 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

- ❑ Update the LED blinking and above project so that: l The LED has two modes of operation: blinking and always ON. l When the board is reset, the LEDs are at the always on mode. 

   - l When the button B1 is pressed, the LEDs will change between the two modes. 

**58** 

**ES, NLT 2026** 

# **<u>Working with Timer</u>** 

❑ Timer: hardware to do things related to counting time or generating intervals and related functions. 

❑ Application of timer: uncountable! 

l Generating events/interrupts, trigger hardware functions with specific interval/frequency. 

   - System timer (systick). 

   - ADC, DAC, wake-up low power CPU,... 

   - Pulse Width Modulation (PWM). 

   - Watchdog. 

- l Measuring time intervals. 

- l Motor control, encoder interfacing, positioning... 

- l Switching for digital power converter… 

❑ STM32F429: 17 timers (p.35-36 Datasheet) 

l Advanced, General purpose, Basic, Watchdogs, Systick. 

**59** 

**ES, NLT 2026** 

# **<u>Working with Timer</u>** 

# ❑ General principal: 

l Organization: 

      - Clock source: from system clock (bus) or external source. 

      - Timer counter registers. 

      - Configuration registers. 

   - l Counter register increase value after each clock period. 

   - l When the counter is carried out, or equals to some threshold: 

      - An event is generated to trigger another peripheral (ADC, DAC…) 

      - Or an interrupt is raised to trigger code execution on CPU. 

- ❑ Programming with Timer: APIs from HAL or LL l HAL_TIM (Time Base, Input Capture, Output Compare, PWM...) l LL_TIM, LL_LPTIM 

   - l HAL_WWDG, LL_WWDG 

**60** 

**ES, NLT 2026** 

# **<u>Basic timer: TIM6 and TIM7</u>** 

- ❑ The basic timers with 16-bit auto-reload counter driven by a 16 bit programmable prescaler. 

- ❑ Able to drive the digital-to-analog converter (DAC). 

- ❑ Basic operation: clock signal from APB1 divided before generating interrupt/event. 

   - Prescaler (16 bit) 

   - Counter period (16 bit) 

_Timer interrupt frequency = fAPB / (Prescaler+1) / (Counter Period + 1)_ 



<!-- Start of picture text -->
Internal clock (CK_INT| Trigger |TRGO,<br>TIMxCLK from RCC — RN onboller DAC<br>r - | Reset, Enable, Count,<br>Ura [Auto-reload Register Ul<br>CK_PSC Stop, Clear or up Jt U Aad<br>COUNTER<br>Prescaler K_CN 7) New<br><!-- End of picture text -->

**61** 

**ES, NLT 2026** 

# **<u>Basic timer: TIM6 and TIM7</u>** 

# ❑ API: HAL_TIM_Base 

l HAL_TIM_Base_Init() l HAL_TIM_Base_DeInit() l HAL_TIM_Base_MspInit() l HAL_TIM_Base_MspDeInit() l HAL_TIM_Base_Start() l HAL_TIM_Base_Stop() l HAL_TIM_Base_Start_IT() l HAL_TIM_Base_Stop_IT() l HAL_TIM_Base_Start_DMA() l HAL_TIM_Base_Stop_DMA() 

**62** 

**ES, NLT 2026** 

# **<u>Working with basic timers</u>** 

# ❑ Exercise 

l Set up system clock at 180 MHz l Write code to blink Red/Green LEDs at 1 Hz 

**63** 

**ES, NLT 2026** 

# **<u>Configuring system clock</u>** 

# ❑ Set up HSE as Crystal/Ceramic Resonator to use the 8 MHz clock from external crystal. 



<!-- Start of picture text -->
Pinout & Configuration Clock Configuration<br>~ Software Packs ~ Pinout<br>qi ioe RCC Mode and Configuration<br>Gatenoriesy) A.>Z<br>syoteonal ® Highligh SpeedSpeed Clock Clock(HSE)(1 :) || Crystal/CeCrystal/Ceramic R Resonatortor v<br>Low Speed Clock (Lse) [Disable<br>* IBYPASS Clock Source<br>DMA RON rrokerteaeteyn crystal/Ceramic Resonator<br>GPIO<br>1w0G O Master Clock Output2<br>QeNVIC t—~—~—SY O Audio Clock Input (128_CKIN)<br>a<br>WWDG<br>Reset Configuration<br>© Parameter Settings (©) User Constants (© NVIC Settings © GPIO Settings<br>Analog ©<br>Search Signals<br>Timers (a) | Search (Ctr#F)<br>*<br>RTC Pin Name Signal on Pin GP1O output le... GPIO mode —GPIO Pull-up/P.... Maximum<br>TmM1 PHO/OSC_IN RCC_OSC_IN nfa n/a n/a infa<br><!-- End of picture text -->

**64** 

**ES, NLT 2026** 

# **<u>Configuring system clock</u>** 

# ❑ Set up clock rate for CPU and buses 

l HCLK: 180 MHz (for CPU) 

l APB1, APB2 timer clocks: 90 MHz (TIM6 and TIM7 use APB1) 



<!-- Start of picture text -->
Pinout & Configuration Clock Configuration Project Manager Tools<br>5 e o esolve C jssues<br>AT Clock Mux<br>fe, sere DY<br>— [Seto] of| a2 | torre oe<br>01000 Hz sine ust [10 enermetor toc ts<br>| | L ef 32 | Terwoc cata) i {160 _|tmemorvand OMA nates<br>some sytemsi  ctfo)PS bo[180]to cones system ter<br>se SYSCLK M2) ANB Prescaler HCL (tz) A) Prescaler r00 | retort cock<br>lO} 180 pele Lasare pertonerat cocks te<br>PLL source tax PLC ‘aco [30] Arorrmercloxs tay<br>ns, PS : areatrencee am<br>Input equency hseae) 14 ~}y{xs.. <p 2 ~ Enable CSS ole vy - 5 |APe2 peripheralclocks (Miz)<br>se— +) ow " 7° #2 Lao] Arseaces te<br>rey! 90 | AtMtteccis (mz)<br>mon 12S sourceMax<br>cee 192 |12Sclocks (ta)<br>L T =x 192 T 2 ve —>o }<br><!-- End of picture text -->

**65** 

**ES, NLT 2026** 

# **<u>Configuring timer 6: frequency</u>** 

# ❑ Activate TIM6 

❑ Prescaler = 89, Counter Period = 99 

- l Timer frequency = 90 MHz / 90 / 100 = 10 KHz l What are appropriate values for frequency of 200 Hz? 



<!-- Start of picture text -->
Pinout & Configuration Clock Configuration<br>~ Software Packs ~ Pinout<br>Q v coy TIM6 Mode and Configuration<br>a) “<br>Tasers a B Actvated<br>© one Pulse Mode<br>atc<br>mm<br>me<br>m3 Configuration<br>osVsams TINS © ResetParameter ConfigurationSettings © user Constants @ NVIC Settings © DMA Settings<br>TM?<br>acme Congr the Blow parameters:<br>Tm10 © Counter Settings<br>Tmtvmie ‘CounterPrescalerMode(PSC - 16 bits value) 89Up<br>maa Counter Period (AutoReload Register - 1... 99<br>ms auto-reload preload Disable<br>Trigger Output (TRGO) Parameters<br>Trigger Event Selection Reset (UG bit from TIMx_EGR)<br>Connectivity ©<br><!-- End of picture text -->

**66** 

**ES, NLT 2026** 

# **<u>Configuring timer 6: interrupt hander</u>** 

# ❑ Enable the TIM6 interrupt handler in NVIC settings 



<!-- Start of picture text -->
Pinout & Configuration Clock Configuration<br>~ Software Packs » Pinout<br>Q © TIM6 Mode and Configuration<br>(Categories) A.>Z<br>Timers @) @ activated“<br>© one Pulse Mode<br>RTC<br>Tm™1<br>TIM2 -<br>13<br>4& Ts TIM4 Reset Configuration<br>V © Parameter Settings ©) User Constants | © NvIC Settings © DMA Settings<br>TIM7 -<br>A Tis NVIC Interrupt Table Ena... Preemption Prio... Sub Prio...<br>TMsTiM10 TIMG global interrupt, DAC1 and DAC2 underrun error interrupts | @ y<br>TiM11<br>TiM12<br>TIM13<br>TiM14<br><!-- End of picture text -->

**67** 

**ES, NLT 2026** 

# **<u>Handing the timer 6 interrupt</u>** 

# ❑ Start the timer 6 



<!-- Start of picture text -->
[maine x [A stm32f4xxitc [8 startup_stm32f429zitxs {0 InterruptEx.ioc<br>87 /* USER CODE END SysInit */<br>88<br>89 /* Initialize all configured peripherals */<br>90 MX GPIO Init();<br>91 MX TIM6 Init();<br>92 /* USER CODE BEGIN 2 */<br>93<br>94 /* USER CODE END 2 */<br>95<br>96 /* Infinite loop */<br>97 /* USER CODE BEGIN WHILE */<br><!-- End of picture text -->

**68** 

**ES, NLT 2026** 

# **<u>Handing the timer 6 interrupt</u>** 

# ❑ Global variable: tim6_count in main.c, extern in ***_it.c 



<!-- Start of picture text -->
@ maine- x [ stm32F4ocitc [8 startup_stm32F429zitxs [J InterruptEx.ioc<br>=<br>45 /* USER CODE BEGIN PV */<br>47 /* USER CODE END PV */<br>48<br><!-- End of picture text -->



<!-- Start of picture text -->
laste ste fc > [set ne eet eso<br>56<br>57 /* External variables ------------<br>J 60 extern int BENGISEEn:<br>61 /* USER CODE END EV */<br>62<br><!-- End of picture text -->



<!-- Start of picture text -->
maine |B stm32F4ocitc x [ startup_stm32f429zitxs [1 InterruptEx.ioc<br>243-void TIM6_DAC_IRQHandler (void)<br>244 {<br>245  /* USER CODE BEGIN TIM6DAC IRQn 0 */<br>246 tim6é_count++;<br>247 if (tim6_count == 5000)|<br>248 {<br>249 tim6_count = 0;<br>250 HAL GPIOTogglePin(GPIOG, GPIOPIN 14);<br>251 }<br>252 /* USER CODE END TIM6DAC IRQn 0 */<br>253 HAL TIMIRQHandler (&htim6) ;<br>254 /* USER CODE BEGIN TIM6DAC IRQn 1 */<br>255<br>256  /* USER CODE END TIM6DAC IRQn 1 */<br>257 }<br><!-- End of picture text -->

**69** 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

- ❑ Configure PA0 as GPIO_EXTI0. 

- ❑ Write code to toggle the red LED when the Blue button (connected to PA0) is double-clicked. 

   - l Double-click condition: two consecutive button click with less than 300 ms interval. 

- ❑ Reference sample code: 



<!-- Start of picture text -->
@ maine (@ stm32f4xxite x [S| startup_stm32f429zitxs Di interruptex.ioc<br>204-void EXTIO_IRQHandler (void)<br>205 {<br>206 /* USER CODE BEGIN EXTIO_IRQn 0 */<br>207 if (tim6_count < 3000)<br>208 {<br>209 HAL GPIO_ TogglePin(GPIOG, GPIOPIN 13);<br>210 }<br>211 tim6_count = 0;<br>212<br>213 /* USER CODE END EXTIO IRQn 0 */<br>214 HAL GPIOEXTI_IRQHandler(GPIO PIN 0);<br>215 /* USER CODE BEGIN EXTIO_TRQn 1 */<br>216<br>217. +/* USER CODE END EXTIO IRQn 1 */<br>218 }<br><!-- End of picture text -->

**70** 

**ES, NLT 2026** 

# **<u>Exercise: interfacing with ultrasonic range sensor</u>** 

- ❑ Connect STM32F429 with the HC-SR04 ultrasonic sensor. 

- ❑ Write code to measure the distance from the sensor to the obstacle when the Blue button is pressed. 

- ❑ This is very easy on Arduino with the ultrasonic sensor library! 

- ❑ But you need to write your own code in this example, to understand how the sensor works 

**71** 

**ES, NLT 2026** 

# **<u>Exercise: interfacing with ultrasonic range sensor</u>** 

# ❑ Ultrasonic range sensor principal 



<!-- Start of picture text -->
HC-SR04 Pinout<br>P td q<br>i HC-SRO4<br>let etal Re<br>|<br>I<br>eeee<br>tia—! __ey<br><!-- End of picture text -->



<!-- Start of picture text -->
?<br>Ag _<br>’<br>For example: e<br>Receiver pulse duration - Time = 1.5ms<br>Speed of sound - Speed = 340m/s = 34cm/s<br>Distance = (Speedx Time) /2<br>Distance = (34cm/msx 1.5ms) /2 = 25.5¢m<br><!-- End of picture text -->



<!-- Start of picture text -->
10 ts Trigger<br>Trig<br>8 cycle sonic burst 4<br>= Output proportional<br>to range“<br>Echo ee | [om<br><!-- End of picture text -->

**Need to measure this pulse width to calculate distance** 

**72** 

**ES, NLT 2026** 

# **<u>Building the circuit</u>** 

# ❑ Connections 

l HC-SR04 VCC: 5V 

l HC-SR04 GND: GND 

- l HC-SR04 Trig: STM32F429 GPIO D14 

l HC-SR04 Echo: STM32F429 GPIO D15 

- ❑ GPIO configuration on STM32F429 

   - l GPIO A0: GPIO_EXTI0, to catch user button pressed interrupt. l D14: GPIO_Output, to generate the Trig pulse. 

   - l D15: GPIO_EXTI15, Rising edge and Falling edge to catch the interrupt on both sides of the Echo pulse. 

   - l Enable the D15 EXTI line 15 interrupt in NVIC 

      - ➔ need to write code in this interrupt hander to measure the duration of the Echo pulse. 

**73** 

**ES, NLT 2026** 

# **<u>Exercise: interfacing with ultrasonic range sensor</u>** 

- ❑ Generate Trig inside EXTI0 interrupt handler 

   - l Raise Trig to 1 when Blue button pressed (interrupt occurs). 

   - l Wait at least 10 us before lowering Trig to 0. 

   - l Note: do not use HAL_Delay inside an interrupt hander, as HAL_Delay uses timer which can has lower priority than EXTI0. 



<!-- Start of picture text -->
[9 main [9 stm32f4xxitcx [S| startup_stm32f429zitxs [J InterruptEx.ioc [Q system_stm32f4xx.c<br>204°void EXTIO IRQHandler (void)<br>205 {<br>206 /* USER CODE BEGIN EXTIO IRQn 0 */<br>207 int t6count = 100;<br>208 HAL GPIOWritePin(GPIOD, GPIO PIN 14, GPIO_PIN SET);<br>209 while (t6count--); //wait at least 10 us<br>210 HAL GPIOWritePin(GPIOD, GPIO PIN 14, GPIO_PIN RESET);<br>211<br>212 /* USER CODE END EXTIO IRQn 0 */<br>213 HAL GPIO_EXTI_ TRQHandler(GPIO PIN 0);<br>214 /* USER CODE BEGIN EXTIO IRQn 1 */<br>215<br>216 /* USER CODE END EXTIO IRQn 1 */<br>217 }<br><!-- End of picture text -->

**74** 

**ES, NLT 2026** 

# **<u>Exercise: interfacing with ultrasonic range sensor</u>** 

- ❑ Measure the Echo pulse width: EXTI15_10 handler 

   - l Note: the handler is called on both sides of the pulse. l Reset timer 6 value upon rising edge of Echo pulse. 

   - l Measure the pulse width by timer 6 value upon falling edge. 

- ❑ Finish the code below to calculate distance 



<!-- Start of picture text -->
[maine —‘[B *stm32F4xx_itcX [9 startup_stm32f429zitxs [J InterruptEx.ioc —_[ system_stm32f4xx.c<br>229-void EXTI15_10 IRQHandler (void)<br>230 {<br>231 /* USER CODE BEGIN EXTI1510 IRQn 0 */<br>232 int state = HAL GPIOReadPin(GPIOD, GPIOPIN 15);<br>233 if (state == GPIO_PIN SET)<br>234 tim6é_count = 0;<br>235 else<br>236 {<br>4237<br>238 }<br>239 HAL GPIOTogglePin(GPIOG, GPIOPIN 14);<br>240 /* USER CODE END EXTI15_10 IRQn 0 */<br>241 HAL GPIO EXTIIRQHandler(GPIOPIN 15);<br><!-- End of picture text -->

**75** 

**ES, NLT 2026** 

# **<u>Exercise: interfacing with ultrasonic range sensor</u>** 

- ❑ Develop new function based on the previous exercise: 

- ❑ Continuously measure X as the distance from sensor to the obstacle: 

l If X < 20 cm: turn on the Red LED, otherwise the Red LED is off. l If X > 50 cm: turn on the Green LED, otherwise Green is off. 

- l If 20 < X < 50 cm: the Green LED is dimmed, with the light intensity inverse proportional with value of X. 

   - X = 50 cm: Green LED turns on completely. 

   - X = 20 cm: Green LED turns off completely. 

**76** 

**ES, NLT 2026** 

# **<u>Controlling LCD 1602</u>** 



❑ LCD 1602: 

l Very popular text LCD l 2 rows x 16 columns 

❑ Block diagram: 



<!-- Start of picture text -->
a<br>\\<br>i} i}<br>| Control signals KS0065BX1 {<br>BO i SEGMENT DRIVER IC<br>~ Or Equiv. |<br>DB7 CONTROLLER |<br>RS u Ic \<br>RW | KSO066U SEG40 |<br>E Or Equiv. | come<br>vss | LCD PANEL |<br>VDD | 16 CHARACTERS X2 LINES \<br>vo ——___.| |<br>\ \<br>BLA I i}<br>BLK CF]|LED BACK LIGHT |<br>\\<br>a<br><!-- End of picture text -->

**77** 77 

**ES, NLT 2026** 

# **<u>LCD 16x2 pinout</u>** 

|**Pin Number**|**Symbol **|**Pin Function**|
|---|---|---|
|1|VSS|Ground|
|2|VCC|+5v|
|3|VEE|Contrast adjustment(VO)|
|4|RS|Register Select.<br>0:Command, 1: Data|
|5|R/W|Read/Write<br>R/W=0: Write<br>R/W=1: Read|
|6|EN|Enable. Fallingedge triggered|
|7|D0|Data Bit 0|
|8|D1|Data Bit 1|
|9|D2|Data Bit 2|
|10|D3|Data Bit 3|
|11|D4|Data Bit 4|
|12|D5|Data Bit 5|
|13|D6|Data Bit 6|
|14|D7|Data Bit 7/BusyFlag|
|15|A/LED+|Back-light Anode(+)|
|16|K/LED-|Back-Light Cathode(-)|





<!-- Start of picture text -->
$8Y os, gsssgassseS<br><!-- End of picture text -->

Note: need to control contrast 

**78** 78 

**ES, NLT 2026** 

# **<u>Timing diagram</u>** 

# ❑ Writing 

l RS = 1: data (character code) l RS = 0: command 



<!-- Start of picture text -->
RS MiVien Vint<br>R/W =F Vius<br><— ars<br>foe<br>/<br>te<br><!-- End of picture text -->

**79** 79 

**ES, NLT 2026** 

# **<u>Interfacing with LCD 16x2</u>** 

❑ Step 1: send command to LCD 

l R/W = 0 (write) l RS = 0 (command) 

❑ Step 2: Send character code to LCD l R/W = 0 (write) l RS = 1 (data) 

**80** 80 

**ES, NLT 2026** 

# **<u>Sample code: send command code</u>** 

```
void LCD_Send_Command(unsigned char x)
```

```
{
```

```
 LCD_DATA=x;//Ma lenh
 RS=0; //Chon thanh ghi lenh
 RW=0; //De ghi du lieu
```

```
 EN=1;
```

```
 Delay_ms(1);
```

```
 EN=0;
```

```
 Delay_ms(1);
```

```
 EN=1;
```

```
}
```

**81** 81 

**ES, NLT 2026** 

# **<u>Sample code: send character code</u>** 

```
void LCD_Write_One_Char(unsigned char c)
```

```
{
```

```
 LCD_DATA=c; //Gia tri du lieu
 RS=1; //Chon thanh ghi du lieu
 RW=0;//Ghi du lieu
 EN=1;
```

```
 Delay_ms(1);
```

```
 EN=0;
```

```
 Delay_ms(1);
 EN=1;
```

```
}
```

**82** 82 

**ES, NLT 2026** 

# **<u>Command set of LCD 16x2</u>** 



<!-- Start of picture text -->
(LT<br>: 1<br>° =<br>=<br>‘ a<br>;<br><!-- End of picture text -->



<!-- Start of picture text -->
Code (Hex) Command to LCD Instruction Register<br>1 Clear display screen<br>2 Return home<br>4 Decrement cursor (shift cursor to left)<br>6 Increment cursor (shift cursor to right)<br>5 Shift display right<br>ih Shift display left<br>8 Display off, cursor off<br>A Display off, cursor on<br>(34 Display on, cursor off<br>E Display on, cursor blinking<br>F Display on, cursor blinking<br>10 Shift cursor position to left<br>14 Shift cursor position to right<br>18 Shift the entire display to the left<br>ic Shift the entire display to the right<br>80 Force cursor to beginning to ist line<br>a) Force cursor to beginning to 2nd line<br>38 2 lines and 5x7 matrix<br><!-- End of picture text -->

**83** 83 

**ES, NLT 2026** 

# **<u>LCD initialization routine</u>** 

```
void LCD_init()
{
```

```
//Chon che do 5x7 pixel, 2 lines
LCD_Send_Command(0x38);
//Bat hien thi, nhap nhay con tro
LCD_Send_Command(0x0E);
LCD_Send_Command(0x01); //Xoa man hinh
LCD_Send_Command(0x80); //Ve dau dong
}
```

**84** 84 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

# ❑ Build circuit with pinout as in the table 

- ❑ Comprehend the sample code 

- ❑ Write code to display the 2 lines on the LCD `Hello K68 ITxxxx` 

```
****************
```

- ❑ Add the code to shift the display content to left/right 

|**LCD 1602**|**STM32F429**<br>**or external**<br>**components**|
|---|---|
|D0|GPIO D14|
|D1|GPIO D15|
|D2|GPIO D12|
|D3|GPIO D13|
|D4|GPIO D10|
|D5|GPIO D11|
|D6|GPIO D8|
|D7|GPIO D9|
|RW|GPIO G2|
|RS|GPIO G4|
|E|GPIO G3|
|VDD|5V|
|VSS|GND|
|VEE/VO|Potential meter<br>output|
|A|5V|
|K|GND|



**85** 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

# ❑ Read distance from ultra-sonic range sensor and display on LCD 1602. 

**86** 

**ES, NLT 2026** 

# **<u>Exercise</u>** 

❑ Write code to display time on LCD 1602 with the following format: 

[hh]:[mm]:[ss]:[s10] 

s10: tenth of second 

❑ Note: 

l Time is measure by using timer 6. 

**87** 

**ES, NLT 2026** 

