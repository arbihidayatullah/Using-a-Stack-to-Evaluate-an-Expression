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

//========================================================================================== Evaluate

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
