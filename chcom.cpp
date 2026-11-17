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
	TOK_INT = 0, // int
	TOK_STR, // STRING
	TOK_CHR, // CHAR
	TOK_DBL, // DOUBLE
	TOK_FLT, // FLOAT
	TOK_BOOL, // BOOLEAN

//			MOD VARIABLES

	TOK_LOG, // LONG
	TOK_SHT, // SHORT
	TOK_SIG, // SIGNED
	TOK_UNS, // UNSIGNED

//			CONDICIONALES

	TOK_IF, // IF
	TOK_ELSE, // ELSE

//			BUCLES

	TOK_FOR, // BUCLE FOR
	TOK_WHILE, // BUCLE WHILE

//                      OTROS
        TOK_IDENT, // NOMBRES DE VARIABLES/ FUNCIONES
        TOK_NUM, // NUMEROS SUELTOS
        TOK_EOF, // FINAL

//		SIMBOLOS-OPERADORES

	TOK_ADD, // +
	TOK_SUB, // -
	TOK_MUL, // *
	TOK_DIV, // /
	TOK_IGU, // =
	TOK_PYC, // ;
	TOK_PAR, // (
	TOK_RAP, // )
	TOK_LLA, // {
	TOK_ALL, // }

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


int main(int argc,char* argv[]){
	if(argc != 2){
		cout<<"[CH COMPILER] Demasiados argumentos";
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
