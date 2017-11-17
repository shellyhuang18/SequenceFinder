#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>
using namespace std;
class SequenceMap{
public:
    SequenceMap() = default;
    ~SequenceMap() = default;

    SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    bool operator<(const SequenceMap &rhs) const{
        return recognition_sequence_ < rhs.recognition_sequence_;
    }
    
    friend ostream &operator<<(ostream &out, const SequenceMap &map){
        for(unsigned int i = 0; i < map.enzyme_acronyms_.size(); ++i){
            cout << map.enzyme_acronyms_[i] << " ";
        }
        return out;
    }

    void Merge(const SequenceMap &other_sequence){
        for(unsigned int i = 0; i < other_sequence.enzyme_acronyms_.size(); ++i){
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }

    const string GetReco(){
        return recognition_sequence_;
    }
private:
    string recognition_sequence_;					
    vector<string> enzyme_acronyms_;	

};

#endif
