// Resolvedor de sistemas de equacao
// Resolve quaisquer sistemas de N incognitas e N equacoes

#include <iostream>
#include <string.h>

using namespace std;

int inc;
int precisao = 2;
double *vals;
string letras = "abcdefghijklmnopqrstuvwxyz";

// retorna true se nao houver "inc" zeros seguidos, seja verticalmente ou horizontalmente
// retorna false se houver "inc" zeros seguidos, o que significa que o sistema nao e determinado
bool check() {
	for (int i = 0; i < inc; i++) {
		// analisa horizontalmente
		if (vals[i * (inc + 1)] == 0)
			for (int j = 1; j < inc; j++)
				if (vals[j - 1 + i * (inc + 1)] != vals[j + i * (inc + 1)])
					break;
				else if (j == inc - 1)
					return false;

		// analisa verticalmente
		if (vals[i] == 0)
			for (int j = 1; j < inc; j++)
				if (vals[i + (j - 1) * (inc + 1)] != vals[i + j * (inc + 1)])
					break;
				else if (j == inc - 1)
					return false;
	}

	return true;
}

// tira aquele monte de zero que o double deixa
string semZ(double num) {
	string str = to_string(num);
	str = str.substr(0, str.find('.') + 1 + precisao);
	str = str.substr(0, str.find_last_not_of('0') + 1);
	if (str.find('.') == str.size() - 1)
		str = str.substr(0, str.size() - 1);
	return str;
}

// procura um numero num vetor
bool find(int *vetor, int num) {
	for (int i = 0; i < inc; i++)
		if (vetor[i] == num)
			return true;
	return false;
}

// desenha bonitinho o sistema de equacoes
void sistema(int qnt, int nvl) {
	string str = "";
	double aux;
	int cont = 0;

	system("cls");
	for (int i = 0; i < nvl; i++) {
		str += "|";
		cont = 0;
		for (int j = 0; j < qnt; j++) {
			aux = vals[j + i * (qnt + 1)];
			if (aux != 0) {
				if (aux < 0)
					str += " -";
				else
					if (str.substr(str.size() - 1, str.size()) != "|")
						str += " +";
				str += " " + ((aux == 1 || aux == -1) ? "" : (aux < 0 ? semZ(aux * -1) : semZ(aux))) + letras[cont++];
			} else
				cont++;
		}
		aux = vals[qnt + i * (qnt + 1)];
		if (str.substr(str.size() - 1, str.size()) != "|")
			str += ((aux < 0) ? " = - " : " = ") + ((aux < 0) ? semZ(aux * -1) : semZ(aux)) + "\n";
		else
			str = str.substr(0, str.size() - 1);
	}

	cout << str;
}

// mostra a matriz pra que eu possa ver se eu programei direito
void printMatriz() {
	for (int i = 0; i < inc; i++) {
		cout << endl;
		for (int j = 0; j < inc + 1; j++)
			cout << vals[j + i * (inc + 1)] << " ";
	}
	cout << endl;
}

// onde a magia acontece
int main(int argc, char *argv[]) {
	inc = 0;
	int cont = 0;
	int num;
	int *pos;
	string aux = "";
	double div = 1;

	/*
	cout << "Insira o Nº de casas decimais visíveis: ";
	cin >> precisao;
	*/

	cout << "Insira a quantidade de incógnitas: ";
	while (true)
		try {
			cin >> aux;
			inc = stoi(aux);
			break;
		} catch (...) {}

	pos = new int[inc];

	for (int i = 0; i < inc; i++)
		pos[i] = -1;

	vals = new double[inc * (inc + 1)];
	for (int i = 0; i < inc; i++) {
		sistema(inc, i);
		for (int j = 0; j < inc - i; j++)
			cout << "|\n";
		
		cout << endl << i + 1 << "ª equação:\n";
		for (int j = 0; j < inc + 1; j++) {
			if (j == inc)
				cout << endl << "Resultado : ";
			else
				cout << endl << j + 1 << "ª incógnita: ";

			while (true)
				try {
					cin >> aux;
					vals[j + i * (inc + 1)] = stod(aux);
					break;
				} catch (...) {}
		}
	}

	sistema(inc, inc);
	printMatriz();

	for (int i = 0; i < inc; i++) {
		if (check()) {
			for (int j = 0; j < inc; j++)
				if (vals[i + j * (inc + 1)] != 0 && !find(pos, j)) {
					pos[cont] = j;
					num = vals[i + j * (inc + 1)];
					for (int k = 0; k < inc + 1; k++)
						vals[k + j * (inc + 1)] /= num;
					break;
				}

			for (int j = 0; j < inc; j++) {
				if (j == pos[cont])
					continue;
				div = vals[i + j * (inc + 1)] / vals[i + pos[cont] * (inc + 1)];
				for (int k = 0; k < inc + 1; k++)
					vals[k + j * (inc + 1)] -= div * vals[k + pos[cont] * (inc + 1)];
			}
			cont++;
		} else {
			cout << "\nEsse sistema não é determinado.";
			return 0;
		}

		printMatriz();
	}

	cout << "\nSolução:\n";
	for (int i = 0; i < inc; i++)
		cout << letras[i] << ": " << vals[inc + i * (inc + 1)] << endl;
}