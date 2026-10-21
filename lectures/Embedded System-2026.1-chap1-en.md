# **Embedded System** 

Ngô Lam Trung Department of Computer Engineering School of Information and Communication Technology (SoICT) Hanoi University of Science and Technology E-mail: trungnl@soict.hust.edu.vn 

**1** 

**ES, NLT 2024** 

# **<u>Course info</u>** 

❑ IT4210E (3-0-1-6). 

❑ Wed 06:45 PM – 09:15 PM + 3 labs. 

❑ Pre-requisites 

l Computer Architecture l Electronics for IT l C programming 

**2** 

**ES, NLT 2024** 

# **<u>Course contents</u>** 

❑ Overview of embedded system organization, including hardware (the MCU, memory, peripherals) and software. ❑ Designing embedded system hardware with basic peripheral devices. 

- ❑ Develop and simulate embedded software based on assembly and high level languages for basic functions, including peripherals (timer/counter, interrupt…), digital input (switch, button, keypad, …), digital output (LEDs, 7- seg LEDs, LED matrix,…), analog interface (ADC,DAC), and serial communications (UART, SPI, I2C, USB,…). 

- ❑ Introduction to embedded RTOS. 

**3** 

**ES, NLT 2024** 

# **<u>What’s the interesting challenge?</u>** 

❑ Embedded system is a very very large field, this course only scratches the surface 

- ❑ Enhanced engineering skills 

   - l Working with hardware layer 

   - l Interfacing with the real physical world 

- ❑ Hands-on experience 

   - l Learning and developing on development kit 

**4** 

**ES, NLT 2024** 

# **<u>Syllabus (tentative)</u>** 

❑ Chap 1: Introduction to embedded systems 

❑ Chap 2: Embedded system organization 

❑ Chap 3: STM32F4 and basic peripheral interfacing 

❑ Chap 4: Serial communication 

- ❑ Chap 5: Real-world interfacing 

- ❑ Chap 6: FreeRTOS 

❑ Chap 7: Arduino 

**5** 

**ES, NLT 2024** 

# **<u>Labs</u>** 

❑ Lab 1: Basic peripheral interfacing 

❑ Lab 2: Serial communication 

❑ Lab 3: Embedded OS/Energy-aware embedded system 

**6** 

**ES, NLT 2024** 

# **<u>Course evaluation</u>** 

- ❑ Progress evaluation: 

   - l Labs 

- ❑ Final exam: quiz + project-based l Teams of 2-3 students 

   - l Project proposed by team (prefered), l or selected from list. 

- ❑ Some samples: 

   - l <u>Syllabus - EE319K (utexas.edu)</u> 

   - l <u>EE319K Lab 10 Videos (utexas.edu)</u> ~~CE~~ 



<!-- Start of picture text -->
YSze i@ms isd aSass a8<br>ee Leren Lae a<br>pai ee maite™ i8 a } e10758<br>* if www.st.com/stm32f4-discovery pe<br>vole) Pg uise a = 8 ofalw<br>bay ha le aaa joe<br>sel = cep he ES<br>fe jeeituba  stwszeazaroisco es. cet<br>rui@estif nes .. as iyeiee<br>miseie (iG) oar<br>m™1@ ©} tS Cs oats<br>ng, UU al pe<br>re jee} lpelea<br>™ 10©; haar<br>je ©; eirce<br>M'@ ©; Satna<br>mule<br>mieemiei | Number of Bubbles joaieuinom<br>mies! oem<br>raosont 4 €: pee1 ofr<br>ries; t peiren<br>150 pains<br>rHmuipe!De! ipaair<br>meio @; Deir<br>nmmee;iwel rfid<br>al7 \@a©; seirou2 @{roi<br>fad4 = i tiieaera<br>cass00 ROL=<br><!-- End of picture text -->

**7** 

**ES, NLT 2024** 

# **<u>References</u>** 

# ❑ Books and lecture notes 

   - l Han-Way Huang, Leo Chartrand 2004, Microcontroller: An Introduction to Software & Hardware Interfacing, Cengage Learning. 

   - l Embedded Systems syllabus from trường Univ. of Cincinnati (EECE 6017C), Univ. of California, Berkeley (EECS 149), Univ. of Pennsylvania (ESE 350), Univ. of Kansas (EECS388) 

- ❑ Technical documents and tools 

   - l Datasheet from chip maker: Atmel, Keil… 

   - l Internet 

   - l Arduino IDE 

   - l STM32Cube IDE 

**8** 

**ES, NLT 2024** 

# **Chapter 1: Introduction** 

**9** 

**ES, NLT 2024** 

# **<u>Content</u>** 

# ❑ What is embedded system 

❑ Embedded application 

❑ Charateristics of embedded systems 

**10** 

**ES, NLT 2024** 

# **Definition** 

## **“Dortmund“ Definition: [Peter Marwedel]** 

**Embedded systems are information processing systems embedded into a larger product.** 

## **<u>Wikipedia:</u>** 

**An embedded system is a computer system with a dedicated function within a larger mechanical or electrical system, often with real-time computing constraints. It is embedded as part of a complete device often including hardware and mechanical parts.** 

**11** 

**ES, NLT 2024** 



# **<u>A sample</u>** 



<!-- Start of picture text -->
ae<br>/<br>(am \<br><!-- End of picture text -->



<!-- Start of picture text -->
™<br><!-- End of picture text -->



<!-- Start of picture text -->
seo =;<br>r i<br><!-- End of picture text -->

**12** 

**ES, NLT 2024** 

# **<u>Another sample: ignition in combustion engine</u>** 



<!-- Start of picture text -->
Four-stroke cycle intake eihawer<br>intake vaive spark plug valves closed valves closed valve closed valve open<br>openoy co Lig/ iia, closedexhaust valveSey(4) | &z | Rezl<br>fie— hE die Bxeu Ne) Baede<br>4 iring<br>combustion by —es —<br>to fe}! fed =<br>wmconnecting — Fe!|= le! , A 43=sLegli= |<br>rod é<br>crankshaft HEELS} e a) oe<br>intake compression power exhaust<br>Air-fuel mixture Air-fuel mixture Explosion forces Piston pushes out<br>is drawn in. is compressed. piston down. burned gases.<br>© 2007 Encyclopedia Britannica, Inc.<br><!-- End of picture text -->



<!-- Start of picture text -->
ya lee<br>‘ S wy<br>; -*<br>a<br><!-- End of picture text -->

Mechanical ignition (distributor) 



<!-- Start of picture text -->
Te J<br>- Wi 7) 4 ne \<br>= ee| “=<br>s A Zi a =<br>7 yoy<br>CUC IC XE MAY LA Gl ?<br>Zz x eA Zz a . A<br>cach phong chong dé xe may khong bi trom IC<br>a<br><!-- End of picture text -->

**13** 

**ES, NLT 2024** 

# **<u>Benefit of embedded system</u>** 

- ❑ Before embedded system 

   - l Logic circuit, hard-wired 

   - l Electro-mechanical control system 

   - l Hydraulic control system 

   - l … 

- ❑ Benefit of embedding and embedded system: l sophisticated control, precise timing, low unit cost, low development cost, high flexibility, small size, and low weight 

- ❑ System/final product will have improved 

   - l Performance 

   - l Features 

   - l Cost 

   - l Dependability 

**14** 

**ES, NLT 2024** 

# **Example** 



<!-- Start of picture text -->
D<br>7<br>ny<br>8 i<br><!-- End of picture text -->





<!-- Start of picture text -->
Canon a<br>—<br>. |<br><!-- End of picture text -->



<!-- Start of picture text -->
j<br>6<br>| e po<br>om =<br><!-- End of picture text -->



<!-- Start of picture text -->
ee, 4 —_— Sa O Ee — SMART HUB<br>AY = Sa —<br>“z — FacebookFo— Netfix —HuluBe Pus YouTube Angry ds 2<br>eon ry 4 3 "<br>aon + S| Bilt ;<br>SS gs |B A<br>a :<br>><br>Wed Bec USASTODA) WwTwit P andos| PyMOG Ma<br>a =: SS<br>‘Asshare ley SPN ScoreCefner sal — hecuWiosther SE _ Skype Semana<br>. SEESK Login) ee(W WalPaper’ETAccount Monagér™ 8) Tools Retur<br><!-- End of picture text -->



<!-- Start of picture text -->
Digital radio Most<br>Vehicle computer mumy SPeaker Fig Mirror ==<br>aneemg HOE- .—windowa  iteUniversal light<br>@%, OHO<br>ws Seat on<br>instruments -_ Heating bt gad eee<br>Additional | vrrmalll WEE Heating A | nesting<br>systems _ Central : Interior (EH m=<br>pie trainaehead body contrr o ! eIIE| yRoof NM BES M, ight YLIN GPSTHank<br>S ae we,_climateeee | beLIN Heating pe ae|<br>Steering wheel| (EE == — —— ne<br>panel f O ——<br>He (EB oe aFB Universaluni  motor<br>vos ieee EE | esses “CEES — universal panel<br>CAN Controller area network<br>GPS Global Positioning System<br>GSM_ Global System for Mobile Communications<br>UN Local interconnect network o<br>MOST Media-oriented systems transport {Leen02)<br><!-- End of picture text -->

**15** 

**ES, NLT 2024** 

# **Automotive electronics** 

- ABS: Anti-lock braking systems 

- ESP: Electronic stability control 

- Airbags 

- Automatic gearboxes 

- Smart keys 

- Blind-angle alert systems 



<!-- Start of picture text -->
|<br>le :<br>, —_ —~ - ~<br>g y ET i<br>aD<br><!-- End of picture text -->

- … 

   - ❑ Up to 100 networked processors 



<!-- Start of picture text -->
Digital radio MOST<br>- Navigation fam Lock Mm lls = Lock Window lift<br>= = © = Universal light<br>[- —— ie<br>| lee % v a CICS<br>—foein0? %o tb rt Seat c Sele<br>systemsAdditional (oa 1 uel a] EES Heating oo ee<br>Drive train ee = inicrior (HS ui=|<br>po eee ere || | = o .<br>e Gitta LIN SOHHIO iM Heating im crs<br>Bx6e | | oO oa |e<br>,<br>steering7 wheel_— SeEQ}| ——aw HE Pe Seat al<br>panel ams. 5 :<br>ee CED | ee . Universal motor<br>FRE speater fee Mirror peony CEE — Universal panel<br>CAN Controller area network<br>GPS Global Positioning System<br>GSM_ Global System for Mobile Communications<br>uN Local interconnect network<br>MOST Media-oriented systems transport {Leen02)<br><!-- End of picture text -->

**16** 

**ES, NLT 2024** 

# **<u>Smart card (vd: SIM card)</u>** 



<!-- Start of picture text -->
Secure Element gas<br>ToD I oD IMob<br>Application Application Application<br>Application API<br>soousy Polley Extensions<br>=|<br>& I<br>sp<br>Java Card JavaCard<br>Environment<br>Java Card<br>Virtual Machine<br>os/BsP Key<br>Oracle Java Card<br>Hardware Platform C) Product Specific<br><!-- End of picture text -->

**17** 

**ES, NLT 2024** 

# **<u>Logistic</u>** 

## l Object tagging : RFID, barcode… 

## l Object tracking. 



<!-- Start of picture text -->
aaveyredsortenae Bu Tussee tzye18s 2578 oe<br>te oeone Sen “Fae<br>(nate srares ss<br>SHIPto. aterSureSEAM suzme53 ett<br>ue<br>GERMANY<br>poysnncetmrisae:| DEU 807 1-00<br>NOsRevere | |<br>UPSecnineEXPRESS#1 123 oe on =tour 2022 1al<br>}<br>or am l el<br>CC-KEY<br>en<br><!-- End of picture text -->



<!-- Start of picture text -->
Location Date Cat. ctivity<br>TOKYO, JP 09/03/2016 3:48P.M. Delivered<br>Tokyo, Japan 09/02/2016 7:10 P.M. Transferred to a local agent for delivery. The delivery<br>will be rescheduled.<br>09/02/2016 7:09 P.M. Thebeingdelivery held forchangea future deliverywas completed.date. / The package is<br>09/02/2016 10:07 AM. A delivery change for this package is in progress. /<br>We've rescheduled this delivery.<br>Tokyo, Japan 08/30/2016 7:18 P.M. The receiver was not available at the time of the final<br>delivery attempt. / We'll contact the sender or receiver<br>about this delivery.<br>08/30/2016 2:28 P.M. The receiverwas not available at the timeof the final<br>delivery attempt.<br>Tokyo, Japan 08/29/2016 11:17 AM. Thesecondreceiver delivery attempt. was not availableA finalatattemptthe time willof be the made<br>08/29/2016 7:48AM. The package is awaiting clearing agency review. /<br>Your package was released by the clearing agency.<br>Tokyo, Japan 08/26/201608/26/2016 2:15P.M.8:30. P.M. wieTransferredThedelivery receiverrescaledattempt.; towasa local notA second availableagent;  attempfor atdelivery. t hewill tim, b e The ofmade.thedelivery first<br>08/26/2016 1:11P.M. Destination Scan<br>08/26/2016 1:00PM. Arrival: Scan<br>08/26/201608/26/2016 12:3812:55 P.M.P.M. DepartureImport ScanScan<br>Narita, Japan 08/26/2016 9:03AM. Arrival Scan<br>08/26/2016 8:44AM. Alte flight has caused a delay. We're adjusting plans<br>and working to deliver your package as quickly as<br>possible.<br>Anchorage, AK, United States 08/25/2016 8:24AM. Departure Scan<br>08/25/2016 6:32AM. Arrival Scan<br>Ontario, CA, United States 08/2 54 /2016 2:21AM.11:10 P.M. ArrivalDeparture Scan Scan<br>Commerce City, CO, United States 08/24/2016 9:55 P.M. Departure Scan<br>Denver, CO, United States 08/24/2016 8:24 P.M. Arrival Scan<br>Boulder, CO, United States 08/24/2016 7:35 P.M. Departure Scan<br>08/24/2016 7:21PM. Origin Scan<br>United States 08/24/2016 5:03 P.M. Order Processed: Ready for UPS<br><!-- End of picture text -->

**18** 

**ES, NLT 2024** 

# **<u>Market size of embedded system (IDC)</u>** 



<!-- Start of picture text -->
Millions of units<br>9,000<br>8,000<br>1000<br>5000<br>5000<br>4000 ee<br>3,000 4<br>2,000<br>6000 —_—_—_——<br>; Oe<br>2005 2006 2007 2008 2009 2010 2011 2012 2013 2014<br>-— Embedded systems —=Personal computers ==Mobile phones<br><!-- End of picture text -->

**19** 

**ES, NLT 2024** 

# **<u>Embedded system market size</u>** 



<!-- Start of picture text -->
Global Embedded System Market Trends<br>USD Bill USD Billior<br>¢ ot « CAGR Tre gobal embecickd system market sizeis estimatedto be USD<br>? Men<br>0 865 billion in 2020 and projectedto reach USD 116.2 billion by<br>Asia Pacificis expected to 6.1% 2025, at aCAGR of 6.196,<br>witness high growth in the<br>near future as it houses =] The increasing global demand for New product developments<br>majorand electronics global semiconductor companies. etlQf  communication equipmentconsumerelectronics equipped with and ria] wouldopportunitiesofferlucrative for market players<br>embedded systemstodrive growth inthe next five years.<br>of embednied systems market<br>© COVID-19 is expected to aversely China is expected to offer<br>ody fool elactronicsimpact the demandand automotive for consumervehicles ,) companieslucrative gr o fferingwth opportunities embeckied for<br>0 1 OA globally, thus, in tum, hampering the components during the forecast<br>market salesfor embedded system period<br>and related components.<br>estimated, pprojected © 2009 - 2020 MatketsandMerkets Resestch Private Lol All tights reserved<br><!-- End of picture text -->

**20** 

**ES, NLT 2024** 

# **<u>1.2 Embedded systems characteristics</u>** 

# ❑ **Dependability** 

- l _Reliability_ R(t) =  probability of system working correctly provided that is was working at t=0 

- l _Maintainability_ M(d) = probability of system working correctly d time units after error occurred. 

- l _Availability_ A(t): probability of system working at time t 

- l _Safety_ : no harm to be caused 

- l _Security_ : confidential and authentic communication 

**21** 

**ES, NLT 2024** 

# **<u>Efficiency and resource constraints</u>** 

# ❑ Efficiency 

l Code-size efficient 

l Run-time efficient 

l Weight efficient l Cost efficient 

l Energy efficient 

❑ Resource constraints 

l Cost 

- l Computing power and storage capacity l Physical size 

- l Energy consumption 

**22** 

**ES, NLT 2024** 



<!-- Start of picture text -->
1000100 oe pe<br>OWex we ea<br>| ott P<br>10 F A\ ogncte™were™aovnginie® weaos——z —"<br>5 \ fd + of<br>a; ee / | A Sa<br>e len<br>0.1 =— 0 WaPo= Hae<br>++ 40,£9]- | QMOPo — +RISC<br>0.01 08 “——oPog + °<br>ae + = ASIC x cell<br>- | FPGA ° MPU<br>0.001 0 4 DSP + RISC<br>° Lo fo} lo °<br>3 S iS S S<br>- 2 a nu a<br><!-- End of picture text -->

**© Hugo De Man, IMEC, Philips, 2007** 

**23** 

**ES, NLT 2024** 

# **<u>Embedded System Hardware</u>** 

❑ Embedded system hardware is frequently used in a loop ( **_“hardware in a loop“_** ): 



<!-- Start of picture text -->
A/D converter information display<br>mple—and—hold processing<br>sae D/A converter<br>(physical<br>environment =<br><!-- End of picture text -->

 **cyber-physical systems** 

**24** 

**ES, NLT 2024** 

# **<u>Responsiveness and Real-time constraints</u>** 

- ❑ React to stimuli from the controlled object or external/internal events within the time allowed. 

- ❑ Many ES must meet **real-time constraints** 

   - l For real-time systems, right answers arriving too late are wrong. - **“A real-time constraint is called hard, if not meeting that constraint could result in a catastrophe“** [Kopetz, 1997]. 

   - l All other time-constraints are called **soft** . 

   - l A guaranteed system response has to be explained without statistical arguments 

**25** 

**ES, NLT 2024** 

# **<u>Dedicated systems for special purpose</u>** 

❑ **Dedicated** towards a certain **application** Knowledge about behavior at design time can  be used to minimize resources and to maximize robustness ❑ **Dedicated user interface** (no mouse, keyboard and screen) 



<!-- Start of picture text -->
Piao O<br><!-- End of picture text -->

**26** 

**ES, NLT 2024** 

# **<u>1.3. Embedded computer organization</u>** 



<!-- Start of picture text -->
Choice<br>More powerful of RAM<br>processor '<br>Ben. feo y<br>= At hg alee fa hee<br>usB-c =  ( oe, | Cigabit<br>Power<br>supply  - y ? 4, \ eerne<br>SupportingMicro HDMI 24KPort: displays Ne 88oy e@iiyeeoy e@iiyee e@iiyeeee<br><!-- End of picture text -->



<!-- Start of picture text -->
88oy e@iiyeeoy e@iiyee e@iiyeeee  ‘tgs l ae KI 58=<br>ep nt aye EB yasorse<br>SE Wrwwstéom/stma2ts-discovery<br>Ree LO lanai mee<br>mesh Ga) 77 RSs<br>zee Number of Bubbles | om<br>mise 3S<br>ag 150 caine<br>coins! rice<br>= a<br><!-- End of picture text -->



<!-- Start of picture text -->
&<br><!-- End of picture text -->



<!-- Start of picture text -->
oe 2 OO son<br>See ARDUINO. Ne<br>ND (Gp eee<br>ee SR<br>lrg)<br>: ~~ ON9) a SERS SSS<br><!-- End of picture text -->



<!-- Start of picture text -->
— TOR a<br>RE oe<br>= itd GRUISAKURA IK<br>=r a isa<br>— ea aa<br>o Samy Beoesecu) aes<br><!-- End of picture text -->

**27** 

**ES, NLT 2024** 

# **<u>1.3. Embedded computer organization</u>** 

❑ System structure 



<!-- Start of picture text -->
=|=]<br>Desktop C omplex embedded Simple embedded<br>computer computer computer<br><!-- End of picture text -->

**28** 

**ES, NLT 2024** 

# **<u>Embedded computer organization</u>** 

# ❑ Central system organization: MCU 



<!-- Start of picture text -->
acceleration,Temperature,vibtation,light, = : Non-volatibecalendlars,dig ital Sonase r ial,memory, analog interfaces, clock/in!<br>magnetic field consors ot) otherprcessors<br>. a [= Non-volatibe memory, volatile<br>Switches, buttons, motors,+——_* J] Digital<br>onloff controls,digital interfacing Sp. cy [7 smnbaEvenuonec<br>Host computer yor+_— i ——— wet<br>— Serial port<br>Simple networks, other computers, ge sell(UART, Bus interface ]<br>Infrared communitcations (IrDA) ——— - Memory<br>Disk drives,audio, analog in, analog :<br>out, parallel (digital) /0,etc.<br>W/O at<br>interfaces Host computers<br><!-- End of picture text -->

**29** 

**ES, NLT 2024** 

# **<u>Processing unit in embedded computer</u>** 

# ❑ Microprocessor: 

   - l CPU packaged as a separate IC. 

   - l Example: Intel Core, AMD Ryzen,… 

- ❑ Microcontroller: (Bộ vi điều khiển) 

   - l A single IC contains basic components of a computer: CPU, Memory (ROM and RAM), basic I/O. 

   - l Example: AVRs from Atmel, PICs from Microchip, STM32F4 (ARM-based) from STMicroelectronics, … 

   - l Architecture: 8 bit, 16 bit, 32 bit, (64 bit). 

   - l On-chip memory or external memory. 

- ❑ SoC (System-on-chip): 

   - l High performance components on a single IC: CPU, GPU, modem… 

   - l Example: Samsung Exynox, Qualcomm Snapdragon, Apple M1… 

**30** 

**ES, NLT 2024** 

# **<u>Memory</u>** 

# ❑ RAM 

❑ ROM, EPROM, EEROM (EEPROM) ❑ Flash: newest ROM technology, market dominating 



<!-- Start of picture text -->
DRAM SRAM NVRAM Flash EEPROM EPROM PROM Masked<br><!-- End of picture text -->

**31** 

**ES, NLT 2024** 

# **<u>Input/Output: peripherals</u>** 

- ❑ Types of peripherals 

   - l Input: sensors, button, switch, knob, ADC… l Output: display, actuators, DAC… 

   - l Communication: UART, SPI, I2C, CAN,… 

l Storage: EEPROM, Flash memory,… 

- ❑ I/O programming 

l Programmed I/O (polling) 

- l Interrupt-driven I/O 

- l Direct Memory Access (DMA) 

**32** 

**ES, NLT 2024** 

# **<u>Exercise</u>** 

# ❑ Read IC datasheet 

l 74HC00 l DS18B20 

- ❑ What is the function of each IC 

- ❑ Footprint of each IC 

- ❑ How each IC works 

**33** 

**ES, NLT 2024** 

# **End of Chap.1** 

**34** 

**ES, NLT 2024** 

