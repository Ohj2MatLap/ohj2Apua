/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main.cpp                                                   #
# Description: Starts executing the program.                       #
#                                                                  #
# Author: Matias Lappalainen, 275852, matias.a.lappalainen@tuni.fi  #
####################################################################
*/

#include "main_window.hh"
#include <QApplication>

/*
 * Ohje!

Matias Lappalainen 275852

Matopeli

Peli käynnistyy painamalla start.
Matoa liikutetaan aswd näppäimillä.
Punainen on ruokaa.
Vihreä madon pää.
Musta madon keho.
Valkoinen peli ruudukkoa.
Pelin loputtua näkee onko voittanut (pelilauta täynnä) vaiko hävinnyt (Mato törmännyt itseensä)

Lisäominaisuudet
-Mato ei törmääkään pelialueen reunaan, vaan kiertää takakautta takaisin pelialueelle. (10 p.)
-Pelissä on Restart-nappula, jolla pelin voi aloittaa uudelleen. (5 p.)
--Play nappula muuttuu restart-nappulaksi pelin käynnistyttyä.
-Pelissä on Pause-nappula, jolla pelin voi tauottaa. (5 p.)
-Kuollessa mato vaihtaa väriä siniseksi (Pää tummansininen).
*/
int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
