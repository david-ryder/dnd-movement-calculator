// DnD Movement Calculator - calculates how movement can be used in DnD, including use of jumps
#include <iostream>
#include <stdlib.h>


using namespace std;

// Character class
class Character {
public:
    double baseMovement;
    double strength;
    double kiPoints;
    double longJump;
    double highJump;
    double spellSlots;

    Character(double a, double b, double c, double d) {
        strength = a;
        baseMovement = b;
        kiPoints = c;
        longJump = strength / 2;
        highJump = ((double)1 / 2) * (3 + ((strength - 10) / 2));
        spellSlots = d;
    }
};

// Extra functions
int menu(double movement, double kiPoints, double spellSlots, double turnsOfJump, bool action, bool bonusAction) {

    // Declaration statements
    int ans;

    // Prints Erick's attributes
    if (turnsOfJump <= 0)
        cout << "Erick has " << movement << " feet of movement, " << kiPoints << " Ki points, and " << spellSlots << " spell slots\n\n";
    else if (turnsOfJump > 0)
        cout << "Erick has " << movement << " feet of movement, " << kiPoints << " Ki points, " << spellSlots << " spell slots, and " << turnsOfJump << " rounds with jump active\n\n";

    cout << "What does Erick do?\n\n";

    // 1 - cast spell
    if (action == true)
        cout << "1 - cast spell\n";
    else
        cout << "\n";

    // 2 - step of the wind
    if (bonusAction == true)
        cout << "2 - step of the wind\n";
    else cout << "\n";

    // 3 - move
    if (movement > 0)
        cout << "3 - move\n";
    else
        cout << "\n";

    // 4 - dash
    if (action == true)
        cout << "4 - dash\n";
    else
        cout << "\n";


    // 5 - attack
    if (action == true)
        cout << "5 - attack\n";
    else
        cout << "\n";

    // 6 - jump
    if (movement > 0)
        cout << "6 - jump\n";
    else
        cout << "\n";

    // 7 - end turn
    cout << "7 - end turn\n";

    // 8 - end combat
    cout << "8 - end combat\n\n";

    cout << "Response: ";

    cin >> ans;

    return ans;
};

void castSpell(bool &action, double &spellSlots, double &turnsOfJump, double &longJump, double &highJump) {
    
    int ans;
    cout << "\nWhich spell?\n\n1 - Jump\n2 - Other spell\n\nResponse: ";
    cin >> ans;

    switch (ans) {
        case 1: {
            action = false;
            spellSlots--;
            turnsOfJump = 10;
            longJump = longJump * 3;
            highJump = highJump * 3;
            cout << "\nJump distance tripled\n\n";
            break;
        }
        case 2: {
            action = false;
            spellSlots--;
            break;
        }
    }

    return;
};

void stepOfTheWind(bool &bonusAction, double &longJump, double &highJump, double &kiPoints, double &movement, double baseMovement, bool &step) {
    
    highJump = highJump * 2;
    longJump = longJump * 2;
    movement = movement + baseMovement;
    kiPoints--;
    bonusAction = false;
    step = true;

    cout << "\nErick dashes as a bonus action, jump height/distance is doubled for this round, 1 Ki point spent\n\n";

    return;
}

void attack(bool &action, double &kiPoints, bool &bonusAction, double &movement) {

    int ans;
    action = false;
    cout << "Erick attacks. Does he use his bonus action for a bonus strike?\n\n1 - yes\n2 - no\n\nResponse: ";
    cin >> ans;
    switch (ans) {
        case 1: {
            bonusAction = false;
            cout << "\nErick uses bonus strike. Does he spend a Ki point to do Flurry of Blows?\n\n1 - yes\n2 - no\n\nResponse: ";
            cin >> ans;
            if (ans == 1) {
                movement += 10;
                kiPoints--;
                cout << "Erick uses Flurry of Blows, gaining 10ft of movement and the benefit of disengage for the turn\n\n";
            }
            else if (ans == 2) {
                cout << "Erick doesn't use Flurry of Blows\n\n";
            }
            break;
        }
        case 2: {
            cout << "Erick doesn't do a bonus strike\n\n";
            break;
        }
    }

    return;
};

void jump(double &previousMovement, double& movement, double longJump, double highJump, double baseLongJump, double baseHighJump) {

    int ans;
    cout << "\nHigh Jump or Long Jump?\n\n1 - high jump\n2 - long jump\n\nResponse: ";
    cin >> ans;
    if (ans == 1) {
        if (previousMovement >= 10) {
            movement = movement - (2 * baseHighJump);
            cout << "\nErick jumps " << 2 * highJump << " feet into the air\n\n";
            previousMovement = 0;
        }
        else {
            movement -= baseHighJump;
            cout << "\nErick jumps " << highJump << " feet into the air\n\n";
            previousMovement = 0;
        }
    }
    else if (ans == 2) {
        if (previousMovement >= 10) {
            movement = movement - (2 * longJump);
            cout << "\nErick jumps " << 2 * longJump << " feet horizontally\n\n";
            if (movement < 0)
                cout << "Erick lands on the next turn\n\n";
            previousMovement = 0;
        }
        else {
            movement -= baseLongJump;
            cout << "\nErick jumps " << longJump << " feet horizontally\n\n";
            previousMovement = 0;
            if (movement < 0)
                cout << "Erick lands on the next turn\n\n";
        }
    }

    return;
};

void dash(double& movement, double baseMovement, bool& action) {

    movement += baseMovement;
    action = false;
    cout << "\nErick dashes, gaining " << baseMovement << " feet to his movement speed\n\n";

    return;
} ;

void fmovement(double& movement, double& previousMovement) {

    int distance;
    bool allowed = false;
    while (allowed == false) {
        cout << "\nHow far does Erick move? (" << movement << "ft max.)\n\nResponse: ";
        cin >> distance;
        if (movement - distance < 0)
            cout << "\nEnter a valid number\n\n";
        else {
            movement = movement - distance;
            previousMovement = distance;
            allowed = true;
        }
    }

    return;
};

void endTurn(double &turnsOfJump, bool &action, bool &bonusAction, double &movement, double &baseMovement, double &highJump, double &longJump, bool &step) {

    action = true;
    bonusAction = true;
    movement = baseMovement;
    if (step == true) {
        highJump = highJump / 2;
        longJump = longJump / 2;
        step = false;
    }

    if (turnsOfJump > 0)
        turnsOfJump--;

    if (turnsOfJump == 0) {
        longJump = longJump / 3;
        highJump = highJump / 3;
    }
    cout << "------------------------------------------------------------------------------\n";
    return;
};

int main() {

    // Enter strength, base movement, ki points, spell slots
    Character Erick(18, 50, 4, 2);

    // Declaration statements
    bool combatActive = true;
    bool action = true;
    bool bonusAction = true;
    bool step = false;
    double movement = Erick.baseMovement;
    double kiPoints = Erick.kiPoints;
    double spellSlots = Erick.spellSlots;
    double longJump = Erick.longJump;
    double highJump = Erick.highJump;
    double baseLongJump = Erick.longJump;
    double baseHighJump = Erick.highJump;
    double turnsOfJump = 0;
    double baseMovement = Erick.baseMovement;
    double previousMovement = 0;
    int ans;

    while (combatActive == true) {

        // Print menu
        ans = menu(movement, kiPoints, spellSlots, turnsOfJump, action, bonusAction);

        switch (ans) {
            case 1: {
                castSpell(action, spellSlots, turnsOfJump, longJump, highJump);
                break;
            }
            case 2: {
                stepOfTheWind(bonusAction, longJump, highJump, kiPoints, movement, baseMovement, step);
                break;
            }
            case 3: {
                fmovement(movement, previousMovement);
                break;
            }
            case 4: {
                dash(movement, baseMovement, action);
                break;
            }
            case 5: {
                attack(action, kiPoints, bonusAction, movement);
                break;
            }
            case 6: {
                jump(previousMovement, movement, longJump, highJump, Erick.longJump, Erick.highJump);
                break;
            }
            case 7: {
                endTurn(turnsOfJump, action, bonusAction, movement, baseMovement, highJump, longJump, step);
                system("cls");
                break;
            }
            case 8: {
                combatActive = false;
                break;
            }
        }
    }

    return 0;
};
