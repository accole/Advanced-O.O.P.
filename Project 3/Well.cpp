#include "Well.h"
#include "UserInterface.h"

void Well::display(Screen& screen, int x, int y)
{
	//display the well border
	for (int i = 0; i < x + 12; i++) {
		for (int j = 0; j < y + 19; j++) {
			if (i == 0 || i == 11) {
				screen.gotoXY(i, j);
				screen.printChar('@');
			}
			else if (j == 18) {
				screen.gotoXY(i, j);
				screen.printChar('@');
			}
		}
	}
}
