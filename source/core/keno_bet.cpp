/*!
 *  This program implements the Keno game.
 *
 *  @file keno_bet.cpp
 *   
 *  @author Fernanda K. Lustosa
 *  @author Paulo V. Andrade
 */

#include "keno_bet.h"
#include <string.h>
#include <iomanip>
#include <locale>

namespace Keno {

void errorMessage(){
    std::cout << "You entered the wrong bet data, use the following format: \n";
    std::cout << "=============================================================\n";
    std::cout << "Credit\n";
    std::cout << "Number of Rounds\n";
    std::cout << "Bet Numbers\n";
    std::cout << "=============================================================\n";
    std::cout << "Remember, one line for each piece of information without empty lines between her\n";
}

bool KenoBet::readFile(std::string betFile){
    std::ifstream file;
    std::cout << ">>> Preparing to read bet file [" << betFile << "], please wait...\n";
    
    std::cout << std::setw(65) << std::setfill('-') << "\n";

    file.open(betFile);

    std::string line;
    bool test=false;

    if(file.is_open()){
        std::cout << "============================================================\n";
        std::cout << "=======================WELCOME TO KENO======================\n";
        std::cout << "============================================================\n";
        getline(file, line);
        
        if( line == " " || line.size()<1 || std::iscntrl(line[0])){
            std::cout << "Invalid Credit: must be between $1 and $10000\n";
            errorMessage();
            exit(0);
        } 

        if(checkMoney(line)){
            getline(file,line);
            if( line == " " || line.size()<1 ){
                std::cout << "Invalid Number of Rounds\n";
                errorMessage();
                exit(0);
            } 

            if(checkRounds(line)){
                getline(file,line);
                if(line == " " || line.size()<1||std::iscntrl(line[0])){
                    std::cout << "Invalid Bet Numbers\n";
                    errorMessage();
                    exit(0);
                }

                if(checkBet(m_spots, line)){
                    test = true;
                }
            }
        }
    }else{
        std::cout << "Enter the path of an existing bet file (e.g. ../../data/bet_01.dat).\n";
            system("exit");
    }

    file.close();
    return test;
}

void KenoBet::initialText(){    

    std::cout << std::fixed << std::setprecision(2);

    std::cout << ">>> Bet successfully read!\n";
    std::cout << std::setw(4) << std::setfill(' ') << "";
    std::cout << "You are going to wage a total of $" << get_wage() << " dollars.\n";

    std::cout << std::setw(4) << std::setfill(' ') << "";
    std::cout << "Going for a total of " << rounds << " rounds, waging $"<< moneyPRound << " per round.\n\n";

    sort(m_spots);

    std::cout << std::setw(4) << std::setfill(' ') << "";
    std::cout << "Your bet has "<<size()<<" numbers. They are: [";
    for(size_t i{0};i<size();i++){
        std::cout << " " <<m_spots[i];
    }
    std::cout <<" ]\n";

    std::cout << std::setw(9) << std::setfill(' ') << "";
    std::cout <<"-------+---------\n         Hits   | Payout  \n         -------+---------\n";
    
    std::ifstream table;

    table.open("../table.txt");

    size_t AuxLine = 0;
    std::string line;

    while( AuxLine!=size() ){
        getline(table, line);
        AuxLine++;
    }

    std::stringstream check1(line);
    std::string intermediate;

    while(getline(check1, intermediate, ' ')){
        payouts.push_back(std::stof(intermediate));
    }

    size_t i=0;
    while( i!=size()+1 ){
        if(payouts[i]>=1){
            std::cout << std::fixed << std::setprecision(0);
        }
        if(i<10){
            std::cout << "         " << i << "      | " << payouts[i] << std::endl;
        }else{
            std::cout << "         " << i << "     | " << payouts[i] << std::endl;
        }

        i++;
    }

    std::cout << std::setw(9) << std::setfill(' ') << "";
    std::cout << std::setw(51) << std::setfill('-') << "\n";

    table.close();
}

void KenoBet::startGame(){
    int currentRound = 0;
    srand(time(NULL));
    std::cout << std::fixed << std::setprecision(2);
    while( currentRound!=rounds ){
        m_wage -= moneyPRound;
        std::cout << std::setw(9) << std::setfill(' ') << "";
        std::cout << "This is round #" << currentRound+1 << " of " << rounds << ", and your wage is $" << moneyPRound << ". Good luck!\n";
        
        std::cout << std::setw(9) << std::setfill(' ') << "";
        std::cout << "The draw numbers are: [ ";

        for (size_t i{0}; i<20; i++){
            int aux = rand() % 80 + 1;
            while( alreadyExist(draw, aux) ){
                aux = rand() % 80 + 1;
            }
            draw.push_back(aux);
        }

        sort(draw);

        for(size_t i{0}; i<draw.size(); i++){
            std::cout << draw[i] << " ";
        }

        std::cout << "]\n\n";

        std::cout << std::setw(9) << std::setfill(' ') << "";
        std::cout << "You hit the following number(s) [";
        hits = find_hits(draw);

        for(size_t i{0}; i<hits.size(); i++){
            std::cout << " " << hits[i];
        }

        m_wage += payouts[hits.size()] * moneyPRound;

        std::cout << " ], a total of " << hits.size() << " hits out of " << size() << ".\n";

        std::cout << std::setw(9) << std::setfill(' ') << "";
        std::cout << "Payout rate is " << payouts[hits.size()] << ", thus you came out with: $" << payouts[hits.size()] * moneyPRound << std::endl;
        
        std::cout << std::setw(9) << std::setfill(' ') << "";
        std::cout << "Your net balance so far is: $" << m_wage << " dollars.\n";

        std::cout << std::setw(9) << std::setfill(' ') << "";
        std::cout << std::setw(51) << std::setfill('-') << "\n";

        reset();
        currentRound++;
    }
    std::cout << ">>> End of rounds!\n";
    std::cout << std::setw(51) << std::setfill('-') << "\n";
}

void KenoBet::sort(Keno::set_of_numbers_type &v)
{
    int aux;
    for(size_t i{1};i<v.size();i++){
        aux = v[i];
        for(size_t j{i}; j>0 && aux<v[j-1]; j--){
            v[j] = v[j-1];
            v[j-1] = aux;
        }
    }
}

bool KenoBet::checkMoney(std::string line){

    size_t count=0;
    for(size_t i{0};i<line.size();i++){
        if(isdigit(line[i])||line[i]=='.'){
            count++;
        }
    }
    if(count == line.size()-1){
        try{
            if( std::stof(line)>0 && std::stof(line)<=10000 ){
                set_wage(std::stof(line));
                return true;
            }
        } catch(std::exception& e){
            std::cout << "Invalid Credit: must be between $1 and $10000\n";
            errorMessage();
            return false;
        }
        
    }
    
    std::cout << "Invalid Credit: must be between $1 and $10000\n";
    system("exit");
    return false;
}

bool KenoBet::checkRounds(std::string line){
    size_t count=0;
    for(size_t i{0};i<line.size();i++){
        if(isdigit(line[i])||line[i]=='.'){
            count++;
        }
    }

    if(count == line.size()-1){

        try{
            if(std::stoi(line)>0){
                setRounds(std::stoi(line));
                moneyPRound = m_wage / std::stoi(line);
                return true;
            }
        } catch(...){
            std::cout << "Invalid Number of Rounds\n";
            return false;
        }
        
    }

    std::cout << "Invalid Number of Rounds\n";
    return false;
}

void KenoBet::setRounds(int roundsP){
    rounds = roundsP;
}

bool KenoBet::checkBet(Keno::set_of_numbers_type v, std::string line){
    std::stringstream check1(line);
    std::string intermediate;

    while(getline(check1, intermediate, ' '))
    {   
        if( intermediate.empty() ){
            getline(check1, intermediate, ' ');
        }

        size_t count=0;
        for(size_t i{0}; i<intermediate.size(); i++){
            if(isdigit(intermediate[i])){
                count++;
            }
        }  
        
        for(size_t i{0};i<intermediate.size();i++){
            if(std::iscntrl(intermediate[i])){
                intermediate = intermediate.substr(0,2);
            }
        }

        if(count == intermediate.size()&&intermediate.size()!=0){
            if( size()<15 ){
                if(std::stoi(intermediate)>=1 && std::stoi(intermediate)<=80){
                    add_spot(std::stoi(intermediate));
                }
            }else{
                std::cout << "Invalid Bet Numbers\n";
                exit(0);
            }
        }
    }
    if(size()>0 && size()<=15){
        return true;
    }

    return false;
}

bool KenoBet::alreadyExist(Keno::set_of_numbers_type &v, Keno::number_type spot){
    for(size_t i{0}; i<v.size(); i++){
            if(v[i]==spot){
                return true; 
            }
        }
    return false;
}

bool KenoBet::add_spot( Keno::number_type spot )
{
    if( m_spots.size()==0 ){
        m_spots.push_back(spot);
        return true;
    }else{
        bool test = alreadyExist(m_spots, spot);
        
        if(test){
            return false;
        }
        
        m_spots.push_back(spot);

        return true;
    }
}

bool KenoBet::set_wage( Keno::cash_type wage )
{
    m_wage = wage;    
    
    if(wage>0){
        return true;
    }
    return false;
}

void KenoBet::reset( void )
{
    draw.clear();
}

Keno::cash_type KenoBet::get_wage( void ) const
{
    return m_wage;
}

size_t KenoBet::size( void ) const
{
    return m_spots.size();
}

Keno::set_of_numbers_type
KenoBet::find_hits( const Keno::set_of_numbers_type & draw ) const
{
    // This container will store all common elements, if any exists.
    Keno::set_of_numbers_type intersection;

    for(size_t i{0};i<size();i++){
        for(size_t j{0};j<draw.size();j++){
            if(m_spots[i]==draw[j]){
                intersection.push_back(draw[j]);
            }
        }
    }

    // Return final count.
    return intersection;
}

Keno::set_of_numbers_type

KenoBet::get_spots( void ) const
{
    return m_spots;
}

void KenoBet::endGame(){
    std::cout << "\n\n===== SUMMARY =====\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << ">>> You spent in this game a total of $" << moneyPRound*rounds << " dollars.\n";

    if( m_wage > moneyPRound*rounds ){
        std::cout << ">>> Hooray, you won $" << m_wage - (moneyPRound*rounds) << " dollars. See you next time! ;-)\n";
    } else if( m_wage == moneyPRound*rounds ){
        std::cout << ">>> Wow, you neither won nor lost. Who knows next time, right?\n";
    } else{
        std::cout << ">>> Too bad, you lost $" << (m_wage - (moneyPRound*rounds))*-1 << " dollars.\n";
    }
    
    std::cout << ">>> You are leaving the Keno table with $" << m_wage << " dollars.\n";
}

} // namespace Keno
//============[ End KenoBet class ]===============//
