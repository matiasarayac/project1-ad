#include "People.h"

int main(int argc, char *argv[]) {

    if (!argv[1] || !argv[2]) {
        cout << "Problems reading parameters" << endl;
        return 0;
    } else {
        People p(argv[1], argv[2]);
    }

    return 0;
}