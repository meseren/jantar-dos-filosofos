#include <iostream>
#include <thread>

using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

//Variável global
int garfos[] = {0, 0, 0, 0, 0};

class Filosofo{

	public:
		int id;

	Filosofo (const int id):id(id){
		cout << "O filosofo " << id << " chegou na mesa!!" << endl;
	}

	public:
		//Cria uma thread para o filósofo
		thread* mesaJantar ()
    {
      return new thread([=] {
				for (int i=0; i < 5; i++) {
					pensar();
					comer();
				}
			});
    }

		void pensar (){
			cout << "O filosofo " << id << " esta pensando..." << endl;

			sleep_for(milliseconds(1000));
		}

		void comer(){

			//Verifica se os garfos adjacentes estão livres
			if(garfos[id] == 0 && garfos[(id+1)%5] == 0){

					//Atualiza o status dos garfos para avisar que está sendo utilizado
					garfos[id] = 1;
					garfos[(id+1)%5] = 1;
					cout << "O filosofo " << id << " esta comendo..." << endl;

					sleep_for(milliseconds(1000));

					//Atualiza o status dos garfos para livre
					garfos[id] = 0;
					garfos[(id+1)%5] = 0;

					cout << "O filosofo " << id << " soltou os garfos!" << endl;
			}else{
				cout << "O filosofo " << id << " nao conseguiu comer..." << endl;
			}
		}
};

int main(){

	thread* threads[5];

	for (int i = 0; i < 5; i++) {
		Filosofo* filosofo = new Filosofo(i);
		threads[i] = filosofo->mesaJantar();
		sleep_for(milliseconds(500));
	}

	for(int i=0; i < 5; i++) {
    threads[i]->join();
  }
}
