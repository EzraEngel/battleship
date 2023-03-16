#include <iostream>

using namespace std;

class ASCII {
  public:

  	void welcome_to() {
      cout << " ____      ____  ________  _____       ______    ___   ____    ____  ________       _________    ___    " << endl;
      cout << "|_  _|    |_  _||_   __  ||_   _|    .' ___  | .'   `.|_   \\  /   _||_   __  |     |  _   _  | .'   `.  " << endl;
      cout << "  \\ \\  /\\  / /    | |_ \\_|  | |     / .'   \\_|/  .-.  \\ |   \\/   |    | |_ \\_|     |_/ | | \\_|/  .-.  \\ " << endl;
      cout << "   \\ \\/  \\/ /     |  _| _   | |   _ | |       | |   | | | |\\  /| |    |  _| _          | |    | |   | | " << endl;
      cout << "    \\  /\\  /     _| |__/ | _| |__/ |\\ `.___.'\\\\  `-'  /_| |_\\/_| |_  _| |__/ |        _| |_   \\  `-'  / " << endl;
      cout << "     \\/  \\/     |________||________| `.____ .' `.___.'|_____||_____||________|       |_____|   `.___.'  " << endl;
  	}

  	void ship(char type) {
      switch (type) {
        case 'A':
          carrier();
          break;
        case 'B':
          battleship();
          break;
        case 'C':
          cruiser();
          break;
        case 'D':
          destroyer();
          break;
        case 'S':
          submarine();
          break;
      }
  	}

  	void carrier() {
      cout << "   ______       _       _______     _______     _____  ________  _______    " << endl; 
      cout << " .' ___  |     / \\     |_   __ \\   |_   __ \\   |_   _||_   __  ||_   __ \\   " << endl; 
      cout << "/ .'   \\_|    / _ \\      | |__) |    | |__) |    | |    | |_ \\_|  | |__) |  " << endl; 
      cout << "| |          / ___ \\     |  __ /     |  __ /     | |    |  _| _   |  __ /   " << endl; 
      cout << "\\ `.___.'\\ _/ /   \\ \\_  _| |  \\ \\_  _| |  \\ \\_  _| |_  _| |__/ | _| |  \\ \\_ " << endl; 
      cout << " `.____ .'|____| |____||____| |___||____| |___||_____||________||____| |___|" << endl; 
  	}

  	void battleship() {
      cout << " ______        _     _________  _________  _____     ________   ______   ____  ____  _____  _______  " << endl; 
      cout << "|_   _ \\      / \\   |  _   _  ||  _   _  ||_   _|   |_   __  |.' ____ \\ |_   ||   _||_   _||_   __ \\ " << endl; 
      cout << "  | |_) |    / _ \\  |_/ | | \\_||_/ | | \\_|  | |       | |_ \\_|| (___ \\_|  | |__| |    | |    | |__) |" << endl; 
      cout << "  |  __'.   / ___ \\     | |        | |      | |   _   |  _| _  _.____`.   |  __  |    | |    |  ___/ " << endl; 
      cout << " _| |__) |_/ /   \\ \\_  _| |_      _| |_    _| |__/ | _| |__/ || \\____) | _| |  | |_  _| |_  _| |_    " << endl; 
      cout << "|_______/|____| |____||_____|    |_____|  |________||________| \\______.'|____||____||_____||_____|   " << endl; 
                                                                                                      
  	}
  	void cruiser() {
      cout << "   ______  _______  _____  _____  _____   ______   ________  _______    " << endl; 
      cout << " .' ___  ||_   __ \\|_   _||_   _||_   _|.' ____ \\ |_   __  ||_   __ \\   " << endl; 
      cout << "/ .'   \\_|  | |__) | | |    | |    | |  | (___ \\_|  | |_ \\_|  | |__) |  " << endl; 
      cout << "| |         |  __ /  | '    ' |    | |   _.____`.   |  _| _   |  __ /   " << endl; 
      cout << "\\ `.___.'\\ _| |  \\ \\_ \\ \\__/ /    _| |_ | \\____) | _| |__/ | _| |  \\ \\_ " << endl; 
      cout << " `.____ .'|____| |___| `.__.'    |_____| \\______.'|________||____| |___|" << endl; 
  	}

  	void destroyer() {
      cout << " ______   ________   ______   _________  _______      ___   ____  ____  ________  _______    " << endl; 
      cout << "|_   _ `.|_   __  |.' ____ \\ |  _   _  ||_   __ \\   .'   `.|_  _||_  _||_   __  ||_   __ \\   " << endl; 
      cout << "  | | `. \\ | |_ \\_|| (___ \\_||_/ | | \\_|  | |__) | /  .-.  \\ \\ \\  / /    | |_ \\_|  | |__) |  " << endl; 
      cout << "  | |  | | |  _| _  _.____`.     | |      |  __ /  | |   | |  \\ \\/ /     |  _| _   |  __ /   " << endl; 
      cout << " _| |_.' /_| |__/ || \\____) |   _| |_    _| |  \\ \\_\\  `-'  /  _|  |_    _| |__/ | _| |  \\ \\_ " << endl; 
      cout << "|______.'|________| \\______.'  |_____|  |____| |___|`.___.'  |______|  |________||____| |___|" << endl; 
  	}

  	void submarine() {
      cout << "  ______  _____  _____  ______   ____    ____       _       _______     _____  ____  _____  ________ " << endl; 
      cout << ".' ____ \\|_   _||_   _||_   _ \\ |_   \\  /   _|     / \\     |_   __ \\   |_   _||_   \\|_   _||_   __  |" << endl; 
      cout << "| (___ \\_| | |    | |    | |_) |  |   \\/   |      / _ \\      | |__) |    | |    |   \\ | |    | |_ \\_|" << endl; 
      cout << " _.____`.  | '    ' |    |  __'.  | |\\  /| |     / ___ \\     |  __ /     | |    | |\\ \\| |    |  _| _ " << endl; 
      cout << "| \\____) |  \\ \\__/ /    _| |__) |_| |_\\/_| |_  _/ /   \\ \\_  _| |  \\ \\_  _| |_  _| |_\\   |_  _| |__/ |" << endl; 
      cout << " \\______.'   `.__.'    |_______/|_____||_____||____| |____||____| |___||_____||_____|\\____||________|" << endl; 
  	}

  	void hit() {
      cout << " ____  ____  _____  _________     " << endl;
      cout << "|_   ||   _||_   _||  _   _  | _  " << endl;
      cout << "  | |__| |    | |  |_/ | | \\_|(_) " << endl;
      cout << "  |  __  |    | |      | |     _  " << endl;
      cout << " _| |  | |_  _| |_    _| |_   (_) " << endl;
      cout << "|____||____||_____|  |_____|      " << endl;
  	}

  	void sunk() {
      cout << "  ______  _____  _____  ____  _____  ___  ____    " << endl; 
      cout << ".' ____ \\|_   _||_   _||_   \\|_   _||_  ||_  _| _ " << endl; 
      cout << "| (___ \\_| | |    | |    |   \\ | |    | |_/ /  (_)" << endl; 
      cout << " _.____`.  | '    ' |    | |\\ \\| |    |  __'.   _ " << endl; 
      cout << "| \\____) |  \\ \\__/ /    _| |_\\   |_  _| |  \\ \\_(_)" << endl; 
      cout << " \\______.'   `.__.'    |_____|\\____||____||____|  " << endl; 
  	}

  	void miss() {
      cout << " ____    ____  _____   ______    ______     " << endl; 
      cout << "|_   \\  /   _||_   _|.' ____ \\ .' ____ \\    " << endl; 
      cout << "  |   \\/   |    | |  | (___ \\_|| (___ \\_|   " << endl; 
      cout << "  | |\\  /| |    | |   _.____`.  _.____`.    " << endl; 
      cout << " _| |_\\/_| |_  _| |_ | \\____) || \\____) | _ " << endl; 
      cout << "|_____||_____||_____| \\______.' \\______.'(_)" << endl;
  	}

  	void invalid() {
      cout << " _____  ____  _____  ____   ____  _       _____     _____  ______     " << endl; 
      cout << "|_   _||_   \\|_   _||_  _| |_  _|/ \\     |_   _|   |_   _||_   _ `.   " << endl; 
      cout << "  | |    |   \\ | |    \\ \\   / / / _ \\      | |       | |    | | `. \\  " << endl; 
      cout << "  | |    | |\\ \\| |     \\ \\ / / / ___ \\     | |   _   | |    | |  | |  " << endl; 
      cout << " _| |_  _| |_\\   |_     \\ ' /_/ /   \\ \\_  _| |__/ | _| |_  _| |_.' /_ " << endl; 
      cout << "|_____||_____|\\____|     \\_/|____| |____||________||_____||______.'(_)" << endl; 
  	}

  	void new_page() {
  	  for (int i=0; i<100; i++) {
  	  	cout << endl;
  	  }
  	}

  	void player() {
  	  cout << "###########################################################################################################" << endl;
  	  cout << "                                                PLAYER                                                     " << endl;
  	  cout << "###########################################################################################################" << endl;
  	}

  	void computer() {
  	  cout << "###########################################################################################################" << endl;
  	  cout << "                                               COMPUTER                                                    " << endl;
  	  cout << "###########################################################################################################" << endl;
  	}
};