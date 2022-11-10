#ifndef _KENO_BET_H_
#define _KENO_BET_H_


/*!
 *  Class the defines a Keno bet.
 *
 *  @author Selan R. dos Santos
 *  @file keno_bet.h
 */

#include "keno_common.h"

namespace Keno
{
    class KenoBet
    {
        public:
            //! Creates a Keno bet.
            /*! A Keno bet stores the player's picked numbers or spots, up to a limit passed as argument.
             *  Any attempt of inserting spots beyond the set limit is ignored.
             *  @param max_n_sposts_ Maximim number of spots this bet may hold.
             */
            KenoBet( ) : m_wage{0.f}
            { /* empty */ }

            //! Open the bet file provided.
            /*! This method tries to open the players bet file.
             *  @param betFile The bet file provided by the player.
             *  @return True if the file opens without problems; False otherwise.
             */
            bool readFile(std::string betFile);

            //! First informs about the match.
            /*! Gives the first information about the game, 
             *    as well as the payout tax according to the amount of numbers bet and the wage per round.
             */
            void initialText();

            //! Perfoms the rounds.
            /*! Provides information about each round, such as the numbers drawn, hits, payout rate, and more.
             */
            void startGame();

            //! Sort given set of numbers.
            /*! Sort a given set of numbers ascending order.
             */
            void sort(Keno::set_of_numbers_type &v);

            //! Check if the value provided is valid.
            /*! This method checks the amount of money wagered.
             *  @param line The bet file line.
             *  @return True if the value is a number greater than zero and less than ten thousand; 
             *   false otherwise.
             */
            bool checkMoney(std::string line);

            //! Check if the number of rounds provided is valid.
            /*! This method checks the number of rounds, sets the number of rounds and count the bet wage for each spin.
             *  @param line The bet file line.
             *  @return True if the number is valid; false otherwise.
             */
            bool checkRounds(std::string line);

            //! Sets the number of rounds.
            /*! This method set the number of game rounds.
             *  @param rounds The rounds number.
             */
            void setRounds(int rounds);

            //! Check bet numbers are valid.
            /*! This method checks the bet numbers and counts only 15 of them. 
             *  @param v The set of bet numbers.
             *  @param line The bet file line.
             *  @return True if the numbers are valid; false otherwise.
             */
            bool checkBet(Keno::set_of_numbers_type v, std::string line);

            //! Checks if number has already been drawn.
            /*! This method verifies if the spot already exists on the draw number collection.
             *  @param v The set of draw numbers.
             *  @param spot Number to be verified and added to the set.
             *  @return True if it has already been draw; False otherwise.
             */
            bool alreadyExist(Keno::set_of_numbers_type &v, Keno::number_type spot);

            //! Adds a number to the player's bet.
            /*! This method adds the number passed as argument to the player's spots
             *  only if the number is not already there.
             *  @param spot The number we wish to include in the bet.
             *  @return Returns true if number chosen is successfuly inserted; false otherwise.
             */
            bool add_spot( Keno::number_type spot );

            //! Sets the player's wage on this bet.
            /*! This method set the amount of money the player is betting.
             *  @param wage The wage.
             *  @return True if we have a wage above zero; false otherwise.
             */
            bool set_wage( Keno::cash_type wage );

            //! Resets a bet to an emtpy state.
            /*! Resets a bet object to an empty state, which means the spot list clered.
            */
            void reset( void );

            //! Recovers the player's wage on this particular bet.
            /*! Retrieves the player's wage on this bet.
             *  @return The wage value.
             */
            Keno::cash_type get_wage( void ) const;

            //! Return the amount of spots currently in the bet.
            /*! Returns to the application the current number of spots in the player's bet.
             *  @return Number of spots present in the bet.
             */
            size_t size( void ) const;

            /*! Determine how many spots from the player's match the hits passed as argument.
             * @param draw List of hits randomly chosen by the computer.
             * @return An vector with the list of hits according to the currently stored bet.
             */
            Keno::set_of_numbers_type
                find_hits( const Keno::set_of_numbers_type & draw ) const;

            //! Return the player's spots.
            /*! Return an std::vector<number_type> with the spots the player has picked so far.
             *  @return The std::vector<number_type> with the plyer's spots picked so far.
             */
            Keno::set_of_numbers_type get_spots( void ) const;

            //! Ends the game.
            /*! It ends the game and tells the player how much was won or lost, 
             *  as well as how much money is left from the initial bet.
             */
            void endGame();
            
        private:
            Keno::cash_type m_wage;             //<! The player's wage.
            Keno::set_of_numbers_type m_spots;  //<! The player's bet, i.e.\ a set of numbers (aka spots).
            Keno::set_of_numbers_type draw;     //<! The randomly chosen draw numbers, i.e.\ a set of numbers (aka draw).
            Keno::set_of_numbers_type hits;     //<! The player's hits according to the draw, i.e.\ a set of numbers (aka hits).
            
            int rounds;                         //<! The number of game rounds.
            int totalPayout = 0;                //<! Calculated payout.
            float moneyPRound;                  //<! Wage amount per round. 
            
            std::vector <float> payouts;        //<! A list of payout values according to the number of hits, each hit equals to an index of this set.
    };
}

#endif
