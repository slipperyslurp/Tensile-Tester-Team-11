# Tensile-Tester-Team-11

1. Repository Contents: Aside from presentation materials and the source code, this repository contains updated design documents and unused code for the stepper motor with gear. Below is the parts list with links as well as special parameters needed to run the code.

2. System Parts: 

Stepper Motor -- 24-48V; 2.8A Motor -- Measures Distance 
https://www.amazon.com/dp/B00PNEPF5I/?coliid=I3ZDFR4H77MWP&colid=TA2UWTAFEFV6&psc=1&ref_=lv_ov_lig_dp_it

Motor Power Supply -- Output: 24V, 4A -> 96W -- Provides necessary power
https://www.amazon.com/dp/B08DHG7PQV/ref=sspa_dk_detail_6?pd_rd_i=B08DHG7PQV&pd_rd_w=11Mib&pf_rd_p=57cbdc41-b731-4e3d-aca7-49078b13a07b&pd_rd_wg=obhFH&pf_rd_r=GPBN1GH0QZRQ2V1AMGM1&pd_rd_r=38017391-f3c6-4365-8c83-a95110ebd574&s=electronics&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFMOE00R1RTM0tEWiZlbmNyeXB0ZWRJZD1BMDQ2OTgxMTJHNlpHWkFBTExCOEUmZW5jcnlwdGVkQWRJZD1BMDU1MTQxNTEySEFIS1dWQU8zVVYmd2lkZ2V0TmFtZT1zcF9kZXRhaWxfdGhlbWF0aWMmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl&th=1

Motor Controller -- 9-42V; Model TB6600 -- Controls System
https://www.amazon.com/OUYZGIA-Chopping-Frequency-20KHZNema-Controller/dp/B08PKJG2ND/ref=asc_df_B08PKJG2ND/?tag=hyprod-20&linkCode=df0&hvadid=475715987248&hvpos=&hvnetw=g&hvrand=12524822550244063853&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9004728&hvtargid=pla-1207686168122&psc=1

20 kg Load Cell with Amplifier Board -- Measures Force
https://www.amazon.com/Bolsen-Tech-Portable-Electronic-Weighing/dp/B07N5KTQ2L/ref=sr_1_2_sspa?crid=3HJHNL923RH17&keywords=load+cell&qid=1648578910&sprefix=load+cell%2Caps%2C151&sr=8-2-spons&psc=1&smid=A2YPMGYKJIIDP8&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyOEhGNjhBQ1BHOFowJmVuY3J5cHRlZElkPUEwNTA3NjM3MkZRWlcyU0s3NTJYWiZlbmNyeXB0ZWRBZElkPUEwNTc4MzExM0w0NktZUTRYUEpWRiZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=

LCD/(I2C protocol controller) -- 20x4 -- Displays Instructions
https://www.amazon.com/SunFounder-Serial-Module-Arduino-Mega2560/dp/B01GPUMP9C/ref=sr_1_6?keywords=lcd%2Bscreen%2Bwith%2Bi2c&qid=1649183651&sprefix=lcd%2Bscreen%2Bwith%2B%2Caps%2C109&sr=8-6&th=1

Switch -- 3 way momentary switch 
https://www.amazon.com/IndusTec-Wired-AMP-12V-Reversing/dp/B07TWNBCJM/ref=sr_1_5?crid=3H1CMQXBBORS&keywords=3+way+momentary+switch+arduino&qid=1649186013&sprefix=3+way+momentary+switch+arduino%2Caps%2C63&sr=8-5

Wing Nuts -- Reinforces the clamps.
Already had in person

String -- Thinner string to maximize accuracy.
Already had in person

3. Software Dependencies:

Libraries:
TimedAction - https://playground.arduino.cc/Code/TimedAction/
LiquidCrystal_I2C-1.1.2 - https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/
HX711-master - https://www.arduino.cc/reference/en/libraries/hx711-arduino-library/

Tools:
ArduSpreadsheet - https://circuitjournal.com/arduino-serial-to-spreadsheet
