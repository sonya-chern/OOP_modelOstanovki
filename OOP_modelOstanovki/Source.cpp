#include<iostream>
#include "windows.h"
#include<time.h>
using namespace std;
class BussStop {											//�����-������� ���������� �� ���������
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
int SumInterval(int ChisloPass, int PassOther);										// ������� ��������� ������� ���������� �������� �� ���������
void RasschetIntervala(int PassOther, int MarshOther, int KolichestvoPass);			 // ������� ��������� ������� �\� �����������
inline void RasschetIntervalaEnd(int PassOther, int MarshOther, int KolichestvoPass); // ������� ��������� �������, ���� ��������� ��������
int main() {
	srand(NULL);
	setlocale(LC_ALL, "rus");
	/*int PassUtro{ 0 }, PassDen{ 0 }, PassVecher{ 0 }, MarshUtro{ 0 }, MarshDen{ 0 }, MarshVecher{ 0 };
	int SrVrPrebPass{ 0 }, KolichestvoPass{ 0 };
	int Vibor{ 0 };
	int TypOst{ 0 };*/
	cout << endl<< "������������ ������ ���������� ���������� �����" << endl<<endl;
	/*do { */
		/*cout << "��� ����������� ������� 1" << endl<< "��� ������ �� ��������� ������� 0" << endl;
		cin >> Vibor;
		if (Vibor == 0) break;
		cout << "������� ��� ���������: 1 - ��������, 2 - �� ��������" << endl;
		cin >> TypOst;
		cout << endl << "������ ������� � ����" << endl;
		Sleep(1500);	system("cls");
		cout << "������� ������� ����� ����� ���������� ���������� �����(���): " << endl;
		cin >> PassUtro;
		cout << "������� ������� ����� ����� ���������� ���������� ����(���): " << endl;
		cin >> PassDen;
		cout << "������� ������� ����� ����� ���������� ���������� �������(���): " << endl;
		cin >> PassVecher;
		cout << endl << "������ ������� � ����" << endl;
		Sleep(1500);	system("cls");
		cout << "������� ������� ����� ����� ���������� ���������� ����� �����(���): " << endl;
		cin >> MarshUtro;
		cout << "������� ������� ����� ����� ���������� ���������� ����� ����(���): " << endl;
		cin >> MarshDen;
		cout << "������� ������� ����� ����� ���������� ���������� ����� �������(���): " << endl;
		cin >> MarshVecher;
		cout << endl << "������ ������� � ����" << endl;
		Sleep(1500);	system("cls");
		�out << "������� ���������� �������, ������� ����� ���������� �� ��������� ������������: " << endl;
		cin >> KolichestvoPass;
		cout << endl << "������ ������� � ����" << endl;
		Sleep(1500);	system("cls");*/

	// ��� �������� ����������������� ������ 91-94, ��� ��������� ������ ������� ���������� � ������������ �������������� ������ 56-88 � 110
		int PassUtro{ 4 }, PassDen{ 8 }, PassVecher{ 3 }; 
		int SrVrPrebPass{ 0 }, KolichestvoPass{ 5 }, MarshUtro{ 8 }, MarshDen{ 10 }, MarshVecher{ 7 };
		int Vibor{ 1 };
		int TypOst{ 2 };
			if (TypOst == 1) {
				cout << "����" << endl;
				RasschetIntervalaEnd(PassUtro, MarshUtro, KolichestvoPass);
				cout << "����" << endl;
				RasschetIntervalaEnd(PassDen, MarshDen, KolichestvoPass);
				cout << "����" << endl;
				RasschetIntervalaEnd(PassVecher, MarshVecher, KolichestvoPass);
			}
			else {
				cout << "����" << endl;
				RasschetIntervala(PassUtro, MarshUtro, KolichestvoPass);
				cout << "����" << endl;
				RasschetIntervala(PassDen, MarshDen, KolichestvoPass);
				cout << "�����" << endl;
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
				cout << "�� ��������� ������� ����� �������, ���������� ��������� ���������� ���������� �� ��������!" << endl;
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
			/*cout << MestVMarsh << " ";*/								// ����� ������� ��������� ����� ����
			A.RemovePass(MestVMarsh);
		}
	}
	if (count) { 
		cout << "������� ����� ���������� �������� �� ���������: " << SrVrPrebivaniaPass/countOst <<" ���"<< endl;
		cout << "�������� ������� ����� ��������� ��������� �����������" << endl;
	}
	A.Clear();
}
inline void RasschetIntervalaEnd(int PassOther, int MarshOther, int KolichestvoPass) {
	if ((MarshOther / PassOther) > KolichestvoPass) {
		cout << "�� ��������� ������� ����� �������, ���������� ��������� ���������� ���������� �� ��������!" << endl;
	}
	else cout << "�������� ������� ����� ��������� ��������� �����������" << endl;
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
