#include <iostream>
#include "routes.hh"
#include "parser.hh"
#include "cli.hh"

//Tekijä: Matias Lappalainen
//Sähköposti: matias.a.lappalainen@tuni.fi
//Opiskelija numero: 275852
//Ohjelman tarkoitus: Lukee suunnistusreitiin liittyvät tiedot ja
//tallentaa ne tietorakenteeseen. Käyttäjä voi komentojen avulla hakea tietoa.

int main()
{
    //Komennot
    //EXIT - Ohjelman suoritus päätty.
    //MAP - Komento tulostaa kartan.
    //ROUTES - Komento tulostaa aakkosjärjestyksessä ranskalaisilla viivoilla allekkain kaikki annetut reitit.
    //ROUTE <reitti> - Komento tulostaa reitille <reitti> kuuluvat rastit kunkin omalle rivilleen nuolella erotetulta.
    //LENGTH <reitti> - Komento tulostaa annetun reitin pituuden.
    //POINTS - Komento tulostaa syötetiedostossa annetut rastit ja niiden tunnukset rastien nimien mukaisessa aakkosjärjestyksessä.
    //RISE <rasti> - Komento tulostaa suurimman jatkuvan nousun, joka voi löytyä, kun annetulta rastilta lähdetään etenemään jotakin reittiä pitkin.

    std::shared_ptr<Routes> routes(new Routes);
    std::cout << "Input> ";
    std::string input;
    getline(std::cin, input);
    if ( !read_input_from_file(input, routes) ){
        return EXIT_FAILURE;
    }
    Cli cli(routes);
    while( cli.exec_prompt() ){ }
    return EXIT_SUCCESS;
}


