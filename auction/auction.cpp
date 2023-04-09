#include <iostream>
#include <vector>
#include <list>
#include <assert.h>

const int MAX_SIZE = 10;

typedef struct _bet {
    int bet;
    int client_id;
} bet_type;

typedef struct _lot {
    char lot_name[MAX_SIZE];
    int max_bet;
    int wining_client_id;
    std::vector<std::vector<bet_type>> bet_history;
} lot;


class Auction {
    public:
        ~Auction() {
            int lot_vector_size = available_lots.size();

            printf ("\n\n");
            printf ("!!!RESULTS!!!\n");

            for (int i = 0; i < lot_vector_size; i ++) {
                print_who_won(i);
            }

            for (int i = 0; i < lot_vector_size; i ++) {
                free (available_lots[i]);
                available_lots[i] = NULL;
            }
        };

        int add_new_client() {
            int to_return = this->user_id;
            int lot_num = get_num_of_lots();

            for (int i = 0; i < lot_num; i ++){
                std::vector<bet_type> client_bet_history;
                available_lots[i]->bet_history.push_back(client_bet_history);
            }
            
            user_id ++;

            return to_return;
        };

        void add_new_lot(const char* lot_name) {
            int name_size = strlen(lot_name);

            if (name_size >= MAX_SIZE) {
                this->~Auction();
                assert (name_size < MAX_SIZE && "NAME SIZE OVERFLOWED");
            }

            lot* new_lot  = (lot*)calloc(1, sizeof(lot));

            strncpy (new_lot->lot_name, lot_name, name_size);
            new_lot->max_bet = 0;
            new_lot->wining_client_id = -1; // no body is winning on init

            available_lots.push_back(new_lot); //added new lot
        };

        void update_max_bet(int lot_id){
            if (lot_id > available_lots.size() - 1) {
                std::cout << "There is no lot with such ID: " << lot_id << "\n";
                return;
            }

            int max_bet = 0;
            int winning_id = -1;

            for (int i = 0; i < user_id; i ++){
                int user_max_bet = get_last_bet(lot_id, i);

                if (user_max_bet > max_bet) {
                    max_bet    = user_max_bet;
                    winning_id = i; 
                }
            }

            available_lots[lot_id]->max_bet          = max_bet;
            available_lots[lot_id]->wining_client_id = winning_id; 
        };

        int get_last_bet(int lot_id, int client_id){
            int bet_size = available_lots[lot_id]->bet_history[client_id].size();
            if (bet_size == 0)
                return 0;

            int last_bet = available_lots[lot_id]->bet_history[client_id][bet_size - 1].bet;

            return last_bet;
        };


        int get_num_of_lots() {
            return available_lots.size();
        };

        void print_who_won(int lot_id){
            if (lot_id > available_lots.size() - 1) {
                std::cout << "There is no lot with such id\n";
                return;
            }

            int winning_id = available_lots[lot_id]->wining_client_id;

            if (winning_id == -1)
                std::cout << "Nobody won! No bets were done for lot: " << available_lots[lot_id]->lot_name << "\n";
            else
                std::cout << "User with ID: " << available_lots[lot_id]->wining_client_id << " won: " << available_lots[lot_id]->lot_name << "\n";
        };

        void print_available_lots() {
            int num_of_lots = available_lots.size();

            for (int i = 0; i < num_of_lots; i ++){
                std::cout << "Lot id " << i << ". Lot name: " << available_lots[i]->lot_name << "\n";
            }

            return;
        };

        std::vector<lot*> available_lots;
    private:
        int user_id = 0;
};

class client {
    public:
        client(Auction& auction_to_join) : auction(auction_to_join) {
            my_id = auction.add_new_client();
        };

        void make_bet(int lot_id, int bet) {
            if (lot_id > auction.available_lots.size() - 1) {
                std::cout << "There is no lot with such id\n";
                return;
            }

            lot* lot_to_bet = auction.available_lots[lot_id];
            
            if (bet <= lot_to_bet->max_bet) {
                std::cout << "Client ID: " << my_id << ". Your bet is too low\n";
            }
            else {
                lot_to_bet->wining_client_id = my_id;
                lot_to_bet->max_bet          = bet;

                int bet_history_size = lot_to_bet->bet_history[my_id].size();

                bet_type new_bet = {};
                new_bet.bet = bet;
                new_bet.client_id = my_id;

                lot_to_bet->bet_history[my_id].push_back(new_bet);
            }
        };

        void cancel_bet(int lot_id) {
            if (lot_id > auction.available_lots.size() - 1) {
                std::cout << "There is no lot with such ID: " << lot_id << "\n";
                return;
            }

            int last_bet = get_last_bet(lot_id);

            if (last_bet == 0)
                return;

            if (last_bet < auction.available_lots[lot_id]->max_bet) {
                auction.available_lots[lot_id]->bet_history[my_id].pop_back();
                return;
            }
            else {
                auction.available_lots[lot_id]->bet_history[my_id].pop_back();
                auction.update_max_bet(lot_id);
            }

            return;
        };

        //for debug only
        void print_bet_history(int lot_id){
            if (lot_id > auction.available_lots.size() - 1) {
                std::cout << "There is no lot with such id\n";
                return;
            }

            int num_of_bets = auction.available_lots[lot_id]->bet_history[my_id].size();

            if (num_of_bets == 0) {
                std::cout << "Client ID: " << my_id << ". You do not have bets for lot with ID: " << lot_id << "\n";
                return;
            }

            std::cout <<"Client ID: " << my_id << ". Your history: [ ";

            for (int i = 0; i < num_of_bets; i ++){
                std::cout <<  auction.available_lots[lot_id]->bet_history[my_id][i].bet << " ";
            }
            std::cout << "] ";
            std::cout << "for lot with ID: " << lot_id << "\n";
        }

        int get_last_bet(int lot_id){
            if (lot_id > auction.available_lots.size() - 1) {
                std::cout << "There is no lot with such ID " << lot_id << "\n";
                return 0;
            }

            int bet_size = auction.available_lots[lot_id]->bet_history[my_id].size();
            if (bet_size == 0){
                std::cout << "You do not have any bets on this lot. " << "Lot ID: " << lot_id << "\n";
                return 0;
            }

            int last_bet = auction.available_lots[lot_id]->bet_history[my_id][bet_size - 1].bet;

            return last_bet;
        };

        int see_my_id() {
            std::cout << "Your id is " << my_id << "\n";
            return my_id;
        };

        int get_max_bet(int lot_id){
            if (lot_id > auction.available_lots.size() - 1) {
                std::cout << "There is no lot with such ID " << lot_id << "\n";
                return 0;
            }
            int max_bet = auction.available_lots[lot_id]->max_bet;
            std::cout << "Max bet for lot with ID: " << lot_id << " is " << max_bet << "\n";

            return max_bet;
        }


        private:
            class Auction& auction;
            int my_id;
};


int main() {
    class Auction my_auction;

    my_auction.add_new_lot("ball");
    my_auction.add_new_lot("plane");
    my_auction.add_new_lot("mouse");

    my_auction.print_available_lots();

    class client client_1(my_auction);
    class client client_2(my_auction);

    client_1.make_bet(0, 10);
    client_1.make_bet(0, 500);

    client_1.print_bet_history(0);

    client_2.make_bet(0, 20);
    client_1.cancel_bet(0);

    client_1.print_bet_history(0);
    client_2.print_bet_history(0);

    return 0;
}