#include <iostream>
#include <memory>
#include "cards.hh"

Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if(top_ == nullptr){
        return false;
    }
    std::shared_ptr<Card_data> item_to_be_removed = top_;
    id = item_to_be_removed->data;
    if(top_->next == nullptr){
        top_=nullptr;
    }
    else{
        top_ = top_->next;
    }

    item_to_be_removed = nullptr;
    return true;
}

void Cards::reverse()
{
    if(top_!=nullptr){
        std::shared_ptr<Card_data> previous = top_;
        std::shared_ptr<Card_data> next_one = previous->next;
        previous->next=nullptr;
        std::shared_ptr<Card_data> new_next;
        while(next_one != nullptr){
            new_next = next_one->next;
            next_one->next=previous;
            previous = next_one;
            next_one = new_next;
        }
        top_ = previous;

    }
}



// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp
