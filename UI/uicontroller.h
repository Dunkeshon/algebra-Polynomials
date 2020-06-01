#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QStringList>
#include <string>
#include "Polynom.h"
#include "Field.h"
using std::vector;
using std::string;

class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList irreducibleStrings READ irreducibleStrings WRITE setIrreducibleStrings NOTIFY irreducibleStringsChanged)
    Q_PROPERTY(QStringList historyStrings READ historyStrings WRITE setHistoryStrings NOTIFY historyStringsChanged)

    Q_PROPERTY(QString mainPolynomialString READ mainPolynomialString WRITE setMainPolynomialString NOTIFY mainPolynomialStringChanged)
    Q_PROPERTY(QString firstOperandString READ firstOperandString WRITE setFirstOperandString NOTIFY firstOperandStringChanged)
    Q_PROPERTY(QString secondOperandString READ secondOperandString WRITE setSecondOperandString NOTIFY secondOperandStringChanged)
    Q_PROPERTY(QString  result READ result WRITE setResult NOTIFY resultChanged)

    QStringList m_irreducibleStrings;

    QStringList m_historyStrings;

    QString m_mainPolynomialString;

    QString m_firstOperandString;

    QString m_secondOperandString;

    QString m_result;

    vector<Polynom> irreduciblesList ;
    vector<Polynom> historyList ;

    Field mainPolynomial ;
    Polynom firstOperandPol;
    Polynom secondOperandPol;
    Polynom resultPol;

    QString parseToQString(Polynom& polynomial){
        QString newString;
        if (polynomial.Polynom::isZero()) {
                newString.push_back("0");
                return newString ;
            }
            Polynom::PElement* tmp = polynomial.Polynom::head;
            int i = 0;
            bool isFirst = true;
            while (tmp != nullptr) {
                if (tmp->key == 0) {
                    tmp = tmp->next;
                    i++;
                    continue;
                }
                if (!isFirst) newString.push_back("+");
                else isFirst = false;
                if (tmp->key != 1 || i == 0)
                    newString.push_back(QString::number(tmp->key)) ;
                if (i != 0) newString.push_back("x^"+QString::number(i));
                tmp = tmp->next;
                i++;
            }
            return newString;
    }

public:
    explicit UiController(QObject *parent = nullptr);
    // для каждого QProperty создать свой эквивалент класса POLYNOMIALS






QStringList irreducibleStrings() const;
QStringList historyStrings() const;


QString mainPolynomialString() const;

QString firstOperandString() const;

QString secondOperandString() const;

QString result() const;

public slots:
void setIrreducibleStrings(QStringList irreducibleStrings);

void clearHistory(){
    m_historyStrings.clear();
    historyList.clear();
    emit historyStringsChanged(m_historyStrings);
}
// end operation and save to history
void updateHistory(){

    historyList.push_back(firstOperandPol);
    historyList.push_back(secondOperandPol);
    historyList.push_back(resultPol);



    firstOperandPol.clear();
    secondOperandPol.clear();
    resultPol.clear();

    m_historyStrings<<m_firstOperandString<<m_secondOperandString<<m_result ;
    emit historyStringsChanged(m_historyStrings);
         m_firstOperandString = "";
         m_secondOperandString = "";
         m_result = "";
         emit firstOperandStringChanged(m_firstOperandString);
         emit secondOperandStringChanged(m_secondOperandString);
         emit resultChanged(m_result);
}

//  end operation and just clear field for the next operation
void clearFields(){
    firstOperandPol.clear();
    secondOperandPol.clear();
    resultPol.clear();
    m_firstOperandString = "";
    m_secondOperandString = "";
    m_result = "";
    emit firstOperandStringChanged(m_firstOperandString);
    emit secondOperandStringChanged(m_secondOperandString);
    emit resultChanged(m_result);
}
// p = 2   1<=q<8
void findIrreducibles(int p, int q){
    // for ui test
//    QStringList newList{"1+ax+bx^2+cx^3","1+ax+bx^2+cx^3+dx^4","1+ax+bx^2+cx^3","1+ax+bx^2+cx^3"
//                           ,"1+ax+bx^2+cx^3","1+ax+bx^2+cx^3+dx^4","1+ax+bx^2+cx^3","1+ax+bx^2+cx^3"
//                           ,"1+ax+bx^2+cx^3","1+ax+bx^2+cx^3+dx^4","1+ax+bx^2+cx^3","1+ax+bx^2+cx^3"};

//    setIrreducibleStrings(newList);
    // Realisation:
    /*
     Vector<Polynomials> IrreduciblePolynomials = mainPolynomial.12Var()
     QStringList newList();
    for(const auto &i:IrreduciblePolynomials)
    {
        newList<<i.getQStringOfPolynom();
    }
     setIrreducibleStrings(newList);
    */

    QStringList newList;
    irreduciblesList = Field::generateIrrpols(p,q);
    for( auto & i : irreduciblesList){
       newList << parseToQString(i);
    }
}

void selectMainPolynom(int index){

    mainPolynomial = irreduciblesList[index];

    m_mainPolynomialString = parseToQString(mainPolynomial);
    emit mainPolynomialStringChanged(m_mainPolynomialString);
}



void setHistoryStrings(QStringList historyStrings);


//input to do




void plus(){
     resultPol=mainPolynomial.add(firstOperandPol,secondOperandPol);
     m_result = parseToQString(resultPol);
     emit resultChanged(m_result);
}
void minus(){
     resultPol=mainPolynomial.subtr(firstOperandPol,secondOperandPol);
     m_result = parseToQString(resultPol);
     emit resultChanged(m_result);
}
void mult(){
     resultPol=mainPolynomial.mult(firstOperandPol,secondOperandPol);
     m_result = parseToQString(resultPol);
     emit resultChanged(m_result);
}
void division(){
     resultPol=mainPolynomial.quot(firstOperandPol,secondOperandPol);
     m_result = parseToQString(resultPol);
     emit resultChanged(m_result);
}
void divMod(){
     resultPol=mainPolynomial.rem(firstOperandPol,secondOperandPol);
     m_result = parseToQString(resultPol);
     emit resultChanged(m_result);
}
void derivate(){
     resultPol=mainPolynomial.derivate(firstOperandPol);
     m_result = parseToQString(resultPol);
     emit resultChanged(m_result);
}
void monic(){
     resultPol=mainPolynomial.monic(firstOperandPol);
     m_result = parseToQString(resultPol);
     emit resultChanged(m_result);
}
void evaluate(int point){

     m_result = QString::number( mainPolynomial.eval(firstOperandPol,point));
     emit resultChanged(m_result);
}
void rootsNumber(){
    m_result = QString::number( mainPolynomial.rootsNumber(firstOperandPol));
    emit resultChanged(m_result);
}
void inverse(){
    resultPol=mainPolynomial.inverse(firstOperandPol);
    m_result = parseToQString(resultPol);
    emit resultChanged(m_result);
}
void gcd(){
    resultPol=mainPolynomial.gcd(firstOperandPol,secondOperandPol);
    m_result = parseToQString(resultPol);
    emit resultChanged(m_result);
}
void buildCircularPolynom(int n){
    resultPol=mainPolynomial.buildCircularPolynom(n);
    m_result = parseToQString(resultPol);
    emit resultChanged(m_result);
}
void isIrreduc(){
    if(mainPolynomial.isIrreduc(firstOperandPol))
        m_result="True";
    else
        m_result="false";
    emit resultChanged(m_result);
}
void irrPolOrder(){
        m_result = QString::number(mainPolynomial.irrPolOrder(firstOperandPol));
        emit resultChanged(m_result);
}


void setMainPolynomialString(QString mainPolynomialString);

void setFirstOperandString(QString firstOperandString);

void setSecondOperandString(QString secondOperandString);

void setResult(QString result);

signals:
void irreducibleStringsChanged(QStringList irreducibleStrings);
void historyStringsChanged(QStringList historyStrings);
void mainPolynomialStringChanged(QString mainPolynomialString);
void firstOperandStringChanged(QString firstOperandString);
void secondOperandStringChanged(QString secondOperandString);
void resultChanged(QString result);
};

#endif // UICONTROLLER_H
