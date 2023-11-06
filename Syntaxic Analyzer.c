#include <stdlib.h>
#include <stdio.h>

#define PV 1
#define P 2
#define VAR 3
#define DP 4
#define ID 5
#define V 6
#define INTEGER 7
#define CHAR 8
#define BEGIN 9
#define END 10
#define OPAFF 11
#define IF 12
#define THEN 13
#define ELSE 14
#define WHILE 15
#define DO 16
#define PO 17
#define PF 18
#define WRITE 19
#define READ 20
#define WRITELN 21
#define READLN 22
#define OPREL 23
#define OPADD 24
#define OPMUL 25
#define PROGRAM 26
#define NB 27

int s;

void erreur() {
    printf("Symbole non accepté !\n");
}

int symbole_suivant() {
    int s;
    printf("Donnez le symbole suivant : ");
    scanf("%d", &s);
    return s;
}

void accepter( int T) {
    if (s == T) {
        s = symbole_suivant();
    } else {
        erreur();
    }
}


void type(){
    if(s== INTEGER){
        accepter(INTEGER);

    }
    else if(s==CHAR){
        accepter(CHAR);

    }
    else{
        erreur();
    }
}


void lprim(){
    if(s==V)
    {
        accepter(V);
        accepter(ID);
        lprim();
    }
    else{
        printf(" lprim ok \n");
    }
}


void listeid(){
    if(s== ID){
        accepter(ID);
        lprim();
    }
    else{
        erreur();
    }
}


void dprim(){
    if(s== VAR ){
        accepter(VAR);
        listeid();
        accepter(DP);
        type();
        accepter(PV);
        dprim();

    }
    else {
        printf("dprim ok \n ");
    }
}


void dcl(){
    dprim();
}


void inst(){
    if( s == ID || s== IF || s== WHILE || s == READ ||  s == READLN || s== WRITELN || s== WRITE )
    {
        listeinst();
    }
    else {
        printf("inst ok\n ");
    }


}


void listeinst(){
    I();
    LIprim();
}


void inst_composee(){
    if(s== BEGIN){
        accepter(BEGIN);
        inst();
        accepter(END);
    }
    else{
        erreur();
    }
}


void ex(){
    exp_simple();
    S();
}


void I(){
    if (s == ID){
        accepter(ID);
        accepter(OPAFF);
        exp_simple();
    }
    else if (s== IF){
        accepter(IF);
        ex();
        accepter(THEN);
        I();
        accepter(ELSE);
        I();
    }
    else if(s == WHILE) {
        accepter(WHILE);
        ex();
        accepter(DO);
        I();
    }
    else if (s == READ){
        accepter(READ);
        accepter(PO);
        accepter(ID);
        accepter(PF);
        accepter(PV);   // add pv

    }
    else if (s == READLN){
        accepter(READLN);
        accepter(PO);
        accepter(ID);
        accepter(PF);
        accepter(PV);   // add pv
    }
    else if (s == WRITE){
        accepter(WRITE);
        accepter(PO);
        accepter(ID);
        accepter(PF);
        accepter(PV);   // add pv
        
    }
    else if (s == WRITELN){
        accepter(WRITELN);
        accepter(PO);
        accepter(ID);
        accepter(PF);
        accepter(PV);   // add pv
    }
    else{
        erreur();
    }
}


void LIprim(){
    if(s== PV){
        accepter(PV);
        I();
        LIprim();

    }else{
        printf("LIprim ok \n");
    }
}


void Tprim(){
    if (s == OPMUL){
        accepter(OPMUL);
        Tprim();
    }else {
        printf("Tprim ok \n");
    }
}


void facteur(){
    if (s== ID){
        accepter(ID);
    }
    else if (s == NB) {
        accepter(NB);
    }
    else if( s== PO){
        accepter(PO);
        exp_simple();
        accepter(PF);
    }
    else {
        printf("facteur ok \n");
    }
}


void terme(){
    facteur();
    Tprim();
}


void Eprim(){
    if (s== OPADD){
        accepter(OPADD);
        terme();
        Eprim();

    }else {
        printf("Eprim ok \n");
    }
}


void exp_simple(){
    terme();
    Eprim();
}
void S(){
    if ( s== OPREL){
        accepter(OPREL);
        exp_simple();

    }else{
        printf("S ok \n");
    }
}


void p() {
    if(s == PROGRAM)
    {
        accepter(PROGRAM);
        accepter(ID);
        accepter(PV);
        dcl();
        inst_composee();


    }
    else {
        erreur();
    }

}

int main() {

    printf("Donnez un symbole : ");
    scanf("%d", &s);
    p();

    return 0;
}

/*
exemple valide:
program test;
var a,b:integer;
Begin
    a:=10;
    readln(b);
*/

/*
exemple non valide:
program 10
*/