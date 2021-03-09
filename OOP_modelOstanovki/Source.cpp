#include<iostream>
#include "windows.h"
#include<time.h>
using namespace std;
class BussStop {											//класс-очередь пассажиров на остановке
	int* Ochered;
	int MaxKolichestvoPass{ 0 }, RazmerOcher{ 0 }, AddIterator{ 0 };
public:
	BussStop() {
		MaxKolichestvoPass = 0, RazmerOcher = 0, AddIterator = 0, Ochered = nullptr;
	}
	BussStop(int MaxKolichestvoPassOther) {
		MaxKolichestvoPass = MaxKolichestvoPassOther;
		Ochered = new int [MaxKolichestvoPass];
		RazmerOcher = 0;
	}
	bool IsFull() {
		return RazmerOcher == MaxKolichestvoPass;
	}
	bool IsEmpty(){ 
		return RazmerOcher == 0;
	}
	bool AddPass() {
		if (!IsFull()) {
			Ochered[RazmerOcher++] = AddIterator++; 
			return 1;
		}
		else return 0;
	}
	void RemovePass(int KolichestvoMest) {
		for (int j = 0; j < KolichestvoMest; j++) {
			if (!IsEmpty()) {
				for (int i = 1; i < RazmerOcher; i++)
					Ochered[i - 1] = Ochered[i];
				RazmerOcher--;
			}
		}
	}
	int GetKolichestvoPassNaOst() {
		return RazmerOcher;
	}
	void Clear() {
		RazmerOcher = 0;
	}
	~BussStop(){
		if (Ochered != nullptr) delete[] Ochered;
	}
};
int SumInterval(int ChisloPass, int PassOther);										// рассчет интервала времени пребывания человека на остановке
void RasschetIntervala(int PassOther, int MarshOther, int KolichestvoPass);			 // рассчет интервала времени м\у маршрутками
inline void RasschetIntervalaEnd(int PassOther, int MarshOther, int KolichestvoPass); // рассчет интервала времени, если остановка конечная
int main() {
	srand(NULL);
	setlocale(LC_ALL, "rus");
	/*int PassUtro{ 0 }, PassDen{ 0 }, PassVecher{ 0 }, MarshUtro{ 0 }, MarshDen{ 0 }, MarshVecher{ 0 };
	int SrVrPrebPass{ 0 }, KolichestvoPass{ 0 };
	int Vibor{ 0 };
	int TypOst{ 0 };*/
	cout << endl<< "Имитационная модель «Остановка маршрутных такси»" << endl<<endl;
	/*do { */
		/*cout << "Для продолжения нажмите 1" << endl<< "Для выхода из программы нажмите 0" << endl;
		cin >> Vibor;
		if (Vibor == 0) break;
		cout << "Укажите тип остановки: 1 - конечная, 2 - не конечная" << endl;
		cin >> TypOst;
		cout << endl << "Данные внесены в базу" << endl;
		Sleep(1500);	system("cls");
		cout << "Введите среднее время между появлением пассажиров утром(мин): " << endl;
		cin >> PassUtro;
		cout << "Введите среднее время между появлением пассажиров днем(мин): " << endl;
		cin >> PassDen;
		cout << "Введите среднее время между появлением пассажиров вечером(мин): " << endl;
		cin >> PassVecher;
		cout << endl << "Данные внесены в базу" << endl;
		Sleep(1500);	system("cls");
		cout << "Введите среднее время между появлением маршрутных такси утром(мин): " << endl;
		cin >> MarshUtro;
		cout << "Введите среднее время между появлением маршрутных такси днем(мин): " << endl;
		cin >> MarshDen;
		cout << "Введите среднее время между появлением маршрутных такси вечером(мин): " << endl;
		cin >> MarshVecher;
		cout << endl << "Данные внесены в базу" << endl;
		Sleep(1500);	system("cls");
		сout << "Введите количество человек, которое может оставаться на остановке одновременно: " << endl;
		cin >> KolichestvoPass;
		cout << endl << "Данные внесены в базу" << endl;
		Sleep(1500);	system("cls");*/

	// для проверки работоспособности строки 91-94, для включения режима запроса информации у пользователя разблокировать строки 56-88 и 110
		int PassUtro{ 4 }, PassDen{ 8 }, PassVecher{ 3 }; 
		int SrVrPrebPass{ 0 }, KolichestvoPass{ 5 }, MarshUtro{ 8 }, MarshDen{ 10 }, MarshVecher{ 7 };
		int Vibor{ 1 };
		int TypOst{ 2 };
			if (TypOst == 1) {
				cout << "Утро" << endl;
				RasschetIntervalaEnd(PassUtro, MarshUtro, KolichestvoPass);
				cout << "День" << endl;
				RasschetIntervalaEnd(PassDen, MarshDen, KolichestvoPass);
				cout << "День" << endl;
				RasschetIntervalaEnd(PassVecher, MarshVecher, KolichestvoPass);
			}
			else {
				cout << "Утро" << endl;
				RasschetIntervala(PassUtro, MarshUtro, KolichestvoPass);
				cout << "День" << endl;
				RasschetIntervala(PassDen, MarshDen, KolichestvoPass);
				cout << "Вечер" << endl;
				RasschetIntervala(PassVecher, MarshVecher, KolichestvoPass);
			}
	/*} while (Vibor);*/
	return 0;
}
void RasschetIntervala(int PassOther, int MarshOther, int KolichestvoPass) {
	BussStop A(KolichestvoPass);
	int count{ 0 }, KolichestvoPassNaOst{ 0 }, SrVrPrebivaniaPass{ 0 }, countOst{ 0 };
	for (int i = 1; i < 6 * 60; i++) {
		if (!(i % PassOther)) {
			if (!A.AddPass()) {
				cout << "На остановке слишком много человек, необходимо увеличить количество транспорта на маршруте!" << endl;
				count = 0;
				break;
			}
			else count++;
		}
		if (!(i % MarshOther)) {
			KolichestvoPassNaOst = A.GetKolichestvoPassNaOst();
			SrVrPrebivaniaPass+=SumInterval(KolichestvoPassNaOst, PassOther);
			countOst++;
			int MestVMarsh = rand() % 15;
			/*cout << MestVMarsh << " ";*/								// можно увидеть рандомное число мест
			A.RemovePass(MestVMarsh);
		}
	}
	if (count) { 
		cout << "Среднее время пребывания человека на остановке: " << SrVrPrebivaniaPass/countOst <<" мин"<< endl;
		cout << "Интервал времени между приходами маршруток достаточный" << endl;
	}
	A.Clear();
}
inline void RasschetIntervalaEnd(int PassOther, int MarshOther, int KolichestvoPass) {
	if ((MarshOther / PassOther) > KolichestvoPass) {
		cout << "На остановке слишком много человек, необходимо увеличить количество транспорта на маршруте!" << endl;
	}
	else cout << "Интервал времени между приходами маршруток достаточный" << endl;
}
int SumInterval(int ChisloPass, int PassOther) {
	int sum{ 0 };
	int tempChisloPass = ChisloPass;
	while (ChisloPass != 0) {
		int temp = ChisloPass * PassOther;
		sum += temp;
		ChisloPass--;
	}
	return sum / tempChisloPass;
}
