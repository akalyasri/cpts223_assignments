#include <map>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char *argv[])
{





    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = {{"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"}};
    TwitterData *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);

       
    }




    // SCENARIO 1 *************************************************************

    map<string, TwitterData> nameMap;
    
    for(int i = 0; i < 5; ++i){

        nameMap[twitter_data[i].getUserName()] = twitter_data[i];
    
    }

    for(const auto& entry : nameMap){

        cout << "Key : " << entry.first << endl;
        cout << "Value : " << entry.second.print() << endl;
    }

    string target = "savage1";

    auto it = nameMap.find(target);

    if(it != nameMap.end()){

        cout << "User " << target << " : " << it->second.print() << " - DELETED" << endl; 
        nameMap.erase(it);

    } else {
        cout << "Username not found" << endl;
    }
    
    // SCENARIO 2 ********************************************************************

    cout << endl << endl << endl <<endl;

    map<string, TwitterData> emailMap;

      for(int i = 0; i < 5; ++i){

        emailMap[twitter_data[i].getUserName()] = twitter_data[i];
    
    }



    for(const auto& entry : emailMap){

        cout << "Key : " << entry.first << endl;
        cout << "Value : " << entry.second.print() << endl;
    }


    string targetEmail = "kat@gmail.com";

    it = emailMap.find(targetEmail);

    if(it != emailMap.end()){

        cout << "User email " << targetEmail << " : " << it->second.print() << " - DELETED" << endl; 
        emailMap.erase(it);

    } else {

        cout << "User email not found" << endl;
    }    

    return 0;
}