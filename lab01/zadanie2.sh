#do zadania 2 wybrałem mutt jako klienta poczty elektronicznej
#!/bin/bash

for adres in `cat adresy.txt`
do
	cat tresc.txt | mutt -s 'Oferta dla firm' $adres -a spec*.pdf 
done
