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
    Q_PROPERTY(QString result READ result WRITE setResult NOTIFY resultChanged)

    QStringList m_irreducibleStrings;

    QStringList m_historyStrings;

    QString m_mainPolynomialString;

    QString m_firstOperandString;

    QString m_secondOperandString;

    QString m_result;


    vector<Polynom> irreduciblesList ;
    Field mainPolynomial ;
    Polynom firstOperandPol;
    Polynom secondOperandPol;
    Polynom resultPol;

    //use ONLY with Polynomials NOT FIELD
    QString parseToQString(Polynom* polynomial){
        QString newString;
        if (polynomial->Polynom::isZero()) {
            newString.push_back("0");
            return newString ;
        }
        Polynom::PElement* tmp = polynomial->Polynom::head;
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

    //  getters do not touch

    QStringList irreducibleStrings() const;

    QStringList historyStrings() const;


    QString mainPolynomialString() const;

    QString firstOperandString() const;

    QString secondOperandString() const;

    QString result() const;

public slots:

    // functions to call from js

    void clearIrreducibles(){
        m_irreducibleStrings.clear();
        irreduciblesList.clear();
    }
    // chech if is prime
    bool isPrime(int number){
        return Polynom::isPrime(number);
    }
    void clearMainPolynomial(){
        m_mainPolynomialString = "";
        mainPolynomial.clear();
    }
    // clear history
    void clearHistory(){
        m_historyStrings.clear();
        emit historyStringsChanged(m_historyStrings);
    }
    // end operation and save to history
    // @param newItem - Qstring in form of ax^2+3 + ax^2-2 = ax^2 + 1 or gcd(...) = (...)
    void updateHistory(QString newItem){
        m_historyStrings<<newItem ;
        emit historyStringsChanged(m_historyStrings);
    }

    //  end operation and just clear field for the next operation
    void clearInputFields(){
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
    void findIrreducibles(QString p, QString q){
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
        bool ok;
        bool ok2;
        irreduciblesList = Field::generateIrrpols(p.toInt(&ok, 10),q.toInt(&ok2, 10));
        for( auto & i : irreduciblesList){
            newList << parseToQString(&i);
        }
        setIrreducibleStrings(newList);
    }

    void selectMainPolynom(int index){

        Polynom newMainPolynom = irreduciblesList[index];

        mainPolynomial.setPolynomAsField(newMainPolynom); // p =2

        m_mainPolynomialString = m_irreducibleStrings[index]; // right
        emit mainPolynomialStringChanged(m_mainPolynomialString);
    }
    //create 2 polynomials from both input fields
    // use in calculate button
    void inputPolynomials(QString firstPolString,QString secondPolString = ""){
        m_firstOperandString = firstPolString;
        m_secondOperandString = secondPolString;
        firstOperandPol = Polynom(mainPolynomial.p,firstPolString.toStdString());
        secondOperandPol = Polynom(mainPolynomial.p,secondPolString.toStdString());
    }
    void plus(){
        resultPol=mainPolynomial.add(firstOperandPol,secondOperandPol);
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void minus(){
        resultPol=mainPolynomial.subtr(firstOperandPol,secondOperandPol);
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void mult(){
        resultPol=mainPolynomial.mult(firstOperandPol,secondOperandPol);
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void division(){
        resultPol=mainPolynomial.quot(firstOperandPol,secondOperandPol);
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void divMod(){
        resultPol=mainPolynomial.rem(firstOperandPol,secondOperandPol);
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void derivate(){
        resultPol=mainPolynomial.derivate(firstOperandPol);
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void monic(){
        resultPol=mainPolynomial.monic(firstOperandPol);
        m_result = parseToQString(&resultPol);
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
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void gcd(){
        resultPol=mainPolynomial.gcd(firstOperandPol,secondOperandPol);
        m_result = parseToQString(&resultPol);
        emit resultChanged(m_result);
    }
    void buildCircularPolynom(int n){
        resultPol=mainPolynomial.buildCircularPolynom(n);
        m_result = parseToQString(&resultPol);
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


    //  setters do not touch
    void setHistoryStrings(QStringList historyStrings);

    void setIrreducibleStrings(QStringList irreducibleStrings);

    void setMainPolynomialString(QString mainPolynomialString);

    void setFirstOperandString(QString firstOperandString);

    void setSecondOperandString(QString secondOperandString);

    void setResult(QString result);

signals:
    //  signals do not touch
    void irreducibleStringsChanged(QStringList irreducibleStrings);
    void historyStringsChanged(QStringList historyStrings);
    void mainPolynomialStringChanged(QString mainPolynomialString);
    void firstOperandStringChanged(QString firstOperandString);
    void secondOperandStringChanged(QString secondOperandString);
    void resultChanged(QString result);
};

#endif // UICONTROLLER_H
