#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
using namespace std;

bool validarNumeroCPF(string cpf, string &msgErro){
    //
    string formatoPadraoCPF = "XXX.XXX.XXX-XX";
    int confirmacao = 0;
    //
    if (cpf.size() != 14){
        msgErro = "O cpf informado nao possui a quantidade certa de caracteres";
        return false;
    }
    if (cpf[3] != '.' or cpf[7] != '.' or cpf[11] != '-'){
        msgErro = "Erro de formatacao(1): o cpf nao segue o padrao" + formatoPadraoCPF + "em que X representa um numero do conjunto {0..9}";
        return false;
    }
    for (int index = 0; index < cpf.size(); index ++) {
        if(index != 3 and index != 7 and index != 11){
            char umCaracter = cpf[index];
            int versaoInteiraCaracter = (int) umCaracter;
            if(versaoInteiraCaracter < 48 or versaoInteiraCaracter > 57){
                msgErro = "Erro de Formatacao (2): o seu cpf não segue o padrao " + formatoPadraoCPF + " em que X representa um numero do conjunto {0..9}";
                return false;
            }
        }
    }

    //
    int primeiroVerificador = cpf[12] - '0';
    int segundoVerificador = cpf[13] - '0';
    //
    const int SIZE_ALL_NUMBERS = 11;
    int arrayWithoutVerificator[SIZE_ALL_NUMBERS - 2] = {0};
    
    for (int indexOriginalArray = 0, indexNewArray = 0 ;indexOriginalArray <  cpf.size(); indexOriginalArray++) {
        if(indexOriginalArray != 3 and indexOriginalArray != 7 and indexOriginalArray != 11 and indexOriginalArray != 12 and indexOriginalArray != 13){
            arrayWithoutVerificator[indexNewArray] = cpf[indexOriginalArray] - '0';
            indexNewArray++;
        }
    }
    
    int only9FirstStep = 0;
    for (int index = 0; index < SIZE_ALL_NUMBERS - 2; index ++) {
        only9FirstStep += arrayWithoutVerificator[index] * (10 - index);
    }
    
    int firstVerificationStep = (only9FirstStep * 10) % 11;
    firstVerificationStep = firstVerificationStep >= 10 ? 0 : firstVerificationStep;
    
    if(firstVerificationStep != primeiroVerificador){
        msgErro = "Erro CPF Invalido (1): nao passou em nossa verificacao!";
        return false;
    }
    
    //
    
    int arrayWithVerificatorOne[SIZE_ALL_NUMBERS - 1] = {0};
    
    for (int indexOriginalArray = 0, indexNewArray = 0 ;indexOriginalArray < cpf.size(); indexOriginalArray++) {
        if(indexOriginalArray != 3 and indexOriginalArray != 7 and indexOriginalArray != 11 and indexOriginalArray != 13){
            arrayWithVerificatorOne[indexNewArray] = cpf[indexOriginalArray] - '0';
            indexNewArray++;
        }
    }
    
    int only10FirstStep = 0;
    for (int index = 0; index < SIZE_ALL_NUMBERS - 1; index ++) {
        only10FirstStep += arrayWithVerificatorOne[index] * (11 - index);
    }
    
    int secondVerificationStep = (only10FirstStep * 10) % 11;
    secondVerificationStep = secondVerificationStep >= 10 ? 0 : secondVerificationStep;
        
    if(secondVerificationStep != segundoVerificador){
        msgErro = "Erro CPF Invalido (2): nao passou em nossa verificacao";
        return false;
    }
    
    //
    
    int firstNumber = cpf[0] - '0';
    int arrayAllNumbers[SIZE_ALL_NUMBERS] = {0};
    int numberEqualNumbers = 0;
    
    for (int indexOriginalArray = 0, indexNewArray = 0 ;indexOriginalArray < cpf.size(); indexOriginalArray++) {
        if(indexOriginalArray != 3 and indexOriginalArray != 7 and indexOriginalArray != 11){
            arrayAllNumbers[indexNewArray] = cpf[indexOriginalArray] - '0';
            indexNewArray++;
        }
    }
    
 
    for (int index = 0 ; index < SIZE_ALL_NUMBERS; index++) {
        if(arrayAllNumbers[index] == firstNumber){
            numberEqualNumbers++;

        }
    }
    
    if(numberEqualNumbers >= SIZE_ALL_NUMBERS){
        msgErro = "Erro CPF Invalido (3): Numeros todos iguais";
        return false;
    }

    msgErro = "CPF Valido";


    
    return true;

}

int main(){
    string digitarCPF = "";
    string msgErro = "";

    cout << "Digita o numero do seu cpf com o seguinte formato substituindo o X pelos numeros: XXX.XXX.XXX-XX: ";
    cin >> digitarCPF;

    validarNumeroCPF(digitarCPF,msgErro);
    cout << msgErro;


    return 0;
}