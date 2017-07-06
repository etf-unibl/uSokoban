# uSokoban #
## Sokoban for MCUs. ##

### English ###

uSokoban has three different levels. After succesfully completed level, next level is being loaded.
Controls are being used for character movement and resetting the current level.
uSokoban supports GLCD display and display used by PC which also needs to run provided GUI.
Those two displays can be active at the same time.

Required hardware:
1. EasyAVR(ATMEGA32A) with 8MHz external clock
2. GLCD 128x64
3. Keyboard (KEYPAD 4x4 mikroE)

Required software:
1. mikroC Pro for AVR
2. AVRFLASH

In order to play the game, you need to connect and to set a few things on EasyAVR:
1. Keyboard 4x4 should be connected to PORTA
2. GLCD should be at its place
3. Turn on switch SW3.1

If you want to use display of a PC, you should:
1. Turn on switches: SW10.1 and SW10.2 (enable UART1)
2. Connect EasyAVR and PC with USB UART cable
3. Set the jumpers J12 and J23 to USB UART mode (similar things need to be done if someone wants to use RS232)
4. Install uSokoban application found at $(PROJECT_ROOT)/tools
5. Run uSokoban application
6. Select one of the available ports that is connected with board
7. Reset EasyAVR
8. Press "Continue" button

You shouldn't use all keys on keyboard 4*4. Only few of them have their function.
Following controls are being used:
UP(8), DOWN(7), LEFT(4), RIGHT(*), RESTART_MAP(* + 0)

In order to program the MCU on the EasyAVR:
1. Connect PC and EasyAVR with USB cable.
2. Turn on the board
3. Run mikroC Pro for AVR
4. Import the project from the codebase (*.mcpav file)
5. Build the project
6. Run AVRFLASH
7. Load .hex file that was generated by the mikroC Pro for AVR
8. Burn the .hex by clicking "Write"

### Srpski/Bosanski ###

uSokoban sadrži tri nivoa, nakon završetka trenutnog nivoa automatski se pokreće sljedeći nivo.
Pored kontrole karaktera koji pokreće kutije igrači su u mogućnosti i da trenutni nivo pokrenu ispočetka u bilo kom trenutku.
Igra Sokoban je implementirana tako da se prikazuje na GLCD-u ili displeju od računara ako se koristi odgovarajući GUI.
Mapu je moguće istovremeno vidjeti i na displeju računara kao i na GLCD-u.

Potreban hardware:
1. EasyAVR(ATMEGA32A) sa kristalom kvarca frekvencije 8 MHz
2. GLCD 128x64
3. Tastatura (KEYPAD 4x4 mikroE)

Potreban software:
1. mikroC Pro for AVR
2. AVRFLASH

Da bi se ploča spremila za rad sa Glcd-om potrebno je učiniti sljedeće:
1. Tastaturu 4x4 treba spojiti na PORTA
2. GLCD postaviti na mjesto predviđeno za GLCD
3. Uključiti prekidač SW3.1

Ukoliko želimo da omogućimo prikaz na displeju računara potrebno je da:
1. Uključimo prekidače SW10.1 i SW10.2 (omogućava se UART1)
2. Odgovarajućim kablom spojimo računar i ploču preko USB UART-a
3. Postaviti jumpere J12 i J23 na USB UART mod (slično važi i za RS232)
4. Instalirati uSokoban aplikaciju koja se nalazi u $(PROJECT_ROOT)/tools
5. Pokrenuti uSokoban aplikaciju
6. Izabrati jedan od dozvoljenih portova koji je povezan sa EasyAVR pločom
7. Resetovati EasyAVR
8. Pritisnuti "Continue" dugme

Potrebno je napomenuti da u toku igre nisu upotrebljivi svi tasteri tastature 4x4.
Koriste se sledeće kontrole:
UP(8), DOWN(7), LEFT(4), RIGHT(*), RESTART_MAP(* + 0)

Za programiranje MCU-a, potrebno je:
1. Spojiti USB kablom ploču i računar.
2. Upaliti ploču
3. Pokrenuti mikroC pro for AVR
4. Importovati projekat u okruženje (*.mcpav fajl)
5. Odraditi build projekta
6. Pokrenemo AVRFLASH
7. Učitamo .hex file koji smo dobili build-ovanjem projekta
8. Učitati .hex file na ciljni MCU