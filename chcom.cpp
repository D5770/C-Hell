#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string_view>
#include <string>

using namespace std;
bool isletter(char letter){
	if(letter >= 'a' && letter <='z' || letter >= 'A' && letter <= 'Z' || letter == '_'){
		return true;
	}else{
		return false;}
}

bool isnumber(char num){
	if(num >= '0' && num <='9'){
		return true;
	}else{
		return false;
	}
}

bool isoperator(char op){
	if(op == '+' || op == '-' ||op == '*'||op == '/' || op == '=' || op == ';' || op == '{' || op == '}' || op == '(' || op == ')'){
		return true;
	}else{
		return false;
	}
}
int in(string l,const vector<string_view> list){
	int var = -1;
	for(int i = 0; i < list.size(); i++){
		if(l == list[i]){
			var = i;
			break;
		}else{
			var = -1;
		}
	}
	return var;
}



enum class TokenType {
//			TIPOS DE VARIABLES
	TOK_INT = 0, // int  0
	TOK_STR, // STRING   1
	TOK_CHR, // CHAR     2
	TOK_DBL, // DOUBLE   3
	TOK_FLT, // FLOAT    4
	TOK_BOOL, // BOOLEAN 5

//			MOD VARIABLES

	TOK_LOG, // LONG	 6
	TOK_SHT, // SHORT    7
	TOK_SIG, // SIGNED   8
	TOK_UNS, // UNSIGNED 9

//			CONDICIONALES

	TOK_IF, // IF        10
	TOK_ELSE, // ELSE    11

//			BUCLES

	TOK_FOR, // FOR      12
	TOK_WHILE, // WHILE  13

//                      OTROS
        TOK_IDENT, // NOMBRES DE VARIABLES/ FUNCIONES   14
        TOK_NUM, // NUMEROS SUELTOS                     15
        TOK_EOF, // FINAL                               16

//		SIMBOLOS-OPERADORES

	TOK_ADD, // +                                       17
	TOK_SUB, // -                                       18
	TOK_MUL, // *                                       19
	TOK_DIV, // /                                       20
	TOK_IGU, // =								21
	TOK_PYC, // ;                                       22
	TOK_PAR, // (								23
	TOK_RAP, // )								24
	TOK_LLA, // {								25
	TOK_ALL, // }								26

};
        const vector<string_view> PALABRAS_CLAVE = {
        "int","str","chr","dbl","flt","bool",
        "log","sht","sig","uns",
        "if","else",
        "for","while"
};

	struct token {
		TokenType tipo;
		string valor;
	};

string leer(string ruta){
	ifstream archivo(ruta);
		if(archivo.is_open()){
			stringstream tolexer;
			tolexer << archivo.rdbuf();
			return tolexer.str();
		}else{return "";}
}


vector<token> tokenizar(string program){
        int i = 0;
        int j = 0;
        vector<token> tokens;
        string guarda;
        while(i < program.size()){
                i = j;
                while(j < program.size()){
                        if(isletter(program[j]) == true){
                                while(j < program.size() && (isletter(program[j]) == true || isnumber(program[j])) == true){// FUNCIONA SI J < PROGRAM.SIZE() ISLET || ISNUM 
					guarda += program[j];
					j++;
				}
				int indice = in(guarda, PALABRAS_CLAVE);
				if(indice != -1){
					tokens.push_back({(TokenType)indice, guarda});
				}else{
					tokens.push_back({TokenType::TOK_IDENT, guarda});
				}
				guarda.clear();



                        }else if(isnumber(program[j]) == true){
				while(j < program.size() &&(isnumber(program[j])) == true){
					guarda += program[j];
					j++;
				}
				tokens.push_back({TokenType::TOK_NUM, guarda});
				guarda.clear();



			}else if(isoperator(program[j]) == true){
				guarda += program[j];
				j++;
				switch(guarda[0]){
				case '+': tokens.push_back({TokenType::TOK_ADD,guarda}); break;
				case '-': tokens.push_back({TokenType::TOK_SUB,guarda}); break;
				case '*': tokens.push_back({TokenType::TOK_MUL,guarda}); break;
				case '/': tokens.push_back({TokenType::TOK_DIV,guarda}); break;
				case '=': tokens.push_back({TokenType::TOK_IGU,guarda}); break;
				case ';': tokens.push_back({TokenType::TOK_PYC,guarda}); break;
				case '(': tokens.push_back({TokenType::TOK_PAR,guarda}); break;
				case ')': tokens.push_back({TokenType::TOK_RAP,guarda}); break;
				case '{': tokens.push_back({TokenType::TOK_LLA,guarda}); break;
				case '}': tokens.push_back({TokenType::TOK_ALL,guarda}); break;
				}
				guarda.clear();



			}else{
                                if(!guarda.empty()){
                                }
                                j++;
                                guarda.clear();
                                break;
                        }
                }
        }
	tokens.push_back({TokenType::TOK_EOF, ""});
        return tokens;
}


/* ############################# PARSER ###############################*/


int parser_variables(vector<token> arch){ //SE LLAMA ARCH POR ARCHIVO, NO CONFUNDIR CON ARCH LINUX XD, AHORA VOY A HACER EL PARSER GGS
	int valor;
	for(int i = 0;i < arch.size();i++){

		if((int)arch[i].tipo >= 0 && (int)arch[i].tipo <= 5){
		}else{valor = 1;return valor;}

		if((int)arch[i + 1].tipo == 21){
		}else{valor = 1;return valor;}

		if((int)arch[i + 2].tipo == 14 || (int)arch[i + 2].tipo == 15){
		}else{valor = 1;return valor;}

		if((int)arch[i + 3].tipo == 22){
			valor = 0;
		}else{valor = 0;return valor;}
	}
	return valor;
}


int parser_funciones(vector<token> arch){
	int valor;
	int num = 3;
	for(int i = 0; i < arch.size();i++){
		if((int)arch[i].tipo >= 0 && (int)arch[i].tipo <= 5){
		}else{valor = 1;return valor;}
		if((int)arch[i + 1].tipo == 21){
		}else{valor = 1;return valor;}
		if((int)arch[i + 2].tipo = 23){
			while((int)arch[i].tipo != 24){
				if((int)arch[i + num].tipo >= 0 && (int)arch[i + num].tipo <= 5){
				}else{valor = 1;return valor;}
				num++;
			}
		}

	}
	return valor;
}





int main(int argc,char* argv[]){
	if(argc != 2){
		cout<<"[CH COMPILER] Demasiados/sin argumentos";
		return 1;
	}
	string codigo = leer(argv[1]);
	vector<token> tokenizado = tokenizar(codigo);
	for(int i = 0; i < tokenizado.size();i++){
		cout<<"Tipo: "<<(int)tokenizado[i].tipo<<" | valor: "<<tokenizado[i].valor<<"\n";
	}

	cout<<"\n";
	return 0;
}
