#include <iostream>

using namespace std;

struct stack{
	double StacK[100000];
	char Stack[100000];
	int top;
};

//========================================================================================== Convert

class Conv{
private:
	stack tumpuk;

public:
	void init(){
		tumpuk.top = -1;
	}

	void push(char input){
			tumpuk.top++;
			tumpuk.Stack[tumpuk.top] = input;
	}

	void pop(){
		tumpuk.top--;
	}

	char Top(){
		return tumpuk.Stack[tumpuk.top];
	}

	bool isEmpty(){
		if(tumpuk.top <= -1)
			return true;
		else
			return false;
	}
}; Conv SC;

//========================================================================================== Evaluate

class Eval{
private:
	stack Tumpuk;

public:
	void push(double input){
			Tumpuk.top++;
			Tumpuk.StacK[Tumpuk.top] = input;
	}

	void pop(){
		Tumpuk.top--;
	}

	double Top(){
		return Tumpuk.StacK[Tumpuk.top];
	}
}; Eval SE;

bool isOperand(char input){
	int c = (int)input;
	if(c >= 48 && c <= 57 || c >= 65 && c <= 90 || c >= 97 && c <= 122)
		return true;
	else
		return false;
}
bool isOperator(char input){
	int c = (int)input;
	if(c == 94 || c >= 42 && c <= 43 || c == 45 || c == 47)
		return true;
	else
		return false;
}
int getlevel(char input){
	if(input == '^')
		return 3;
	else if(input == '*' || input == '/')
		return 2;
	else if(input == '+' || input == '-')
		return 1;
	else if(input == '(' || input == ')')
		return 0;
	else
		return -1;
}
bool precedence(char input1, char input2){
	int c1 = getlevel(input1);
	int c2 = getlevel(input2);

	if(c1 <= c2)
		return true;
	else
		return false;
}
string InfixtoPostfix(string input){
	SC.init();
	int i=0;
	string P = "";
	while(input[i] != '\0'){
		if(isOperand(input[i])){
			P += input[i];
		}
		if(input[i] == '('){
			SC.push(input[i]);
		}
		if(input[i] == ')'){
			while(!SC.isEmpty() && SC.Top() != '('){
				P = P + " " + SC.Top(); SC.pop();
			}
			SC.pop();
		}
		if(isOperator(input[i])){
			if(SC.isEmpty() || SC.Top() == '('){
				SC.push(input[i]);
			}else{
				while(!SC.isEmpty() && SC.Top() != '(' && precedence(input[i], SC.Top())){
					P = P + " " + SC.Top(); SC.pop();
				}
				SC.push(input[i]);
			}
		}
		if(isOperator(input[i]))
			P += " "; 
		i++;
	}
	while(!SC.isEmpty()){
		P = P + " " + SC.Top(); SC.pop();
	}
	return P;
}
double pow(double number, double exp){
	for(int i=1; i<exp; i++)
		number *= number;
	return number;
}
bool Operand(char input){
	int c = (int)input;
	if(c >= 48 && c <= 57)
		return true;
	else if(c >= 65 && c <= 90 || c >= 97 && c <= 122){
		cout << "\nNot Evaluated" << endl;
		cin.get();
		exit(0);
	}
	else
		return false;
}
double Operation(double op1, char c, double op2){
	if(c == '^')
		return (pow(op1,op2));
	else if(c == '*')
		return (op1 * op2);
	else if(c == '/')
		return (op1 / op2);
	else if(c == '+')
		return (op1 + op2);
	else if(c == '-')
		return (op1 - op2);	
	else return 0;
}
double Evaluate(string input){
	int i = 0;
	while(input[i] != '\0'){
		if(Operand(input[i])){
			double operand = 0;
			while(input[i] != '\0' && Operand(input[i])){
				operand = (operand * 10) + (input[i] - 48);
				i++;
			}
			SE.push(operand);
		}
		if(isOperator(input[i])){
			double A = SE.Top(); SE.pop();
			double B = SE.Top(); SE.pop();
			double result = Operation(B,input[i],A);
			SE.push(result);
		}
		i++;
	}
	return SE.Top();
}


int main(){
	string i;
	cout<<"\t================================ "<<endl;
	cout<<"nama anggota :  1.aulia ahmad nabil"<<endl;
	cout<<"\t\t2.asbiq alawi"<<endl;
 	cout<<"\t\t3.arbi hidayatullah"<<endl;
	cout<<"\t\t4.pandi barep arianza"<<endl;
	cout<<"\t================================="<<endl<<endl;
	cout<<"Enter Infix Expression = " << endl;
	cout << (char)62 << (char)62 << " ";
	getline(cin,i);
	string P = InfixtoPostfix(i);
	cout << "\nInfix    = " << i;
	cout << "\nPostfix  = " << P;
	double result = Evaluate(P);
	cout << "\nEvaluate = " << result;

	cin.get();
	return 0;
}
