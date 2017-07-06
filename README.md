# uSokoban
# Sokoban for MCUs.

Igra Sokoban sadrži tri nivoa, nakon završetka trenutnog nivoa automatski se pokreće sljedeći nivo.
Pored kontrole karatkera koji pokreće kutije igrači su u mogućnosti i da trenutni nivo pokrenu ispočetka u bilo kom trenutku.
Igra Sokoban je implementirana tako da se može igrati na Glcd-u ili preko računara koristeći serijsku komunikaciju.
Mapu je moguće istovremeno vidjeti i na monitoru računara kao i na Glcd-u.

Potreban hardware:
1. AVR razvojna ploca (Atmega32) sa kristalom kvarca frekvencije oscilovanja 8 MHz
2. Glcd 128x64
3. Tastatura (KEYPAD 4x4 mikroE)

Potreban software:
1. mikroC pro for AVR
2. AVRFLASH


Da bi se ploča spremila za rad sa Glcd-om potrebno je učiniti sljedeće:
1. Tastaturu 4x4 treba spojiti na PORTA
2. Glcd postaviti na mjesto predviđeno za Glcd
3. Uključiti svič SW3.1

Ukoliko želimo da omogućimo i rad preko serijske komunikacije potrebno je da:
1. Uključimo  svičeve SW10.1 i SW10.2, oni omogucavaju UART1
2. Odgovarajućim kablom spojimo računar i ploču preko USB UART-a
3. Postaviti jumper-e J12 i J23 na USB UART mod

Potrebno je napomenuti da u toku igre nisu upotrebljivi svi tasteri tastature 4x4, odnosno programski je realizovano da se tastatura koristi kao 3x2
pri čemu se sljedeći tasteri koriste za igru (4,5,7,8,*,0).
UP(8), DOWN(7), LEFT(4), RIGHT(*), RESTART_MAP(* + 0)

Nakon što podesimo ploču i spojimo spoljašnje komponente potrebno je spustiti kod na sljedeći način:
1. Spojimo USB kablom ploču i računar.
2. Upalimo ploču
3. Pokrenemo mikroC pro for AVR
4. Učitamo projekat koji smo prethodno povukli sa Github-a
5. Kompajliramo projekat
6. Pokrenemo AVRFLASH
7. Učitamo .hex file koji smo dobili kompajliranjem
8. Spustimo to na ploču pritiskom na dugme Write
