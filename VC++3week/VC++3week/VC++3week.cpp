#include <iostream>
#include <conio.h>
#include <time.h>

int main()
{
	char buffer[100];
	int index = 0;
	char code;
	char input;
	double et_d = 0, st_d = 0;

	while (1) {

		if (_kbhit()) {
			code = _getch();

			if (code == 27) {
				return(0);
			}
			else if (code == -32) {
				input = _getch();
				if (input == 72) {
					buffer[index] = 'U';
				}
				else if (input == 80) {
					buffer[index] = 'D';
				}
				else if (input == 77) {
					buffer[index] = 'R';
				}
				else if (input == 75) {
					buffer[index] = 'L';
				}
				index++;
			}
			else if (code >= 32 && code <= 126) {
				buffer[index] = code;
				index++;
				code = 0;
			}

			
		}

		if (index != 0) {
			clock_t et = clock();
			et_d = et / 1000;

			if (et_d - st_d >= 0.3) {
				index = 0;
			}
			else {
				if (buffer[0] == 'D' && buffer[1] == 'R' && buffer[2] == 'a') {
					printf("아도겐! =o\n");
					index = 0;
					buffer[2] = 'x';
				}
				else if (buffer[0] == 'U' && buffer[1] == 'U' && buffer[2] == 'D' && buffer[3] == 'D' && buffer[4] == 'z') {
					printf("견제기\n");
					index = 0;
				}
				else if (buffer[0] == 'U' && buffer[1] == 'D' && buffer[2] == 'R' && buffer[3] == 'R' && buffer[4] == 'z') {
					printf("주력기\n");
					index = 0;
				}
				else if (buffer[0] == 'R' && buffer[1] == 'L' && buffer[2] == 'U' && buffer[3] == 'R' && buffer[4] == 'z') {
					printf("각성기\n");
					index = 0;
				}

				clock_t st = clock();
				st_d = st / 1000;

				buffer[4] = 'x';
			}
		}
		else {
			clock_t st = clock();
			st_d =  st / 1000;
		}
		
	}
}
