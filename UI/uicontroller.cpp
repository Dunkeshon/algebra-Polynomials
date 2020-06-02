#include "uicontroller.h"

UiController::UiController(QObject *parent) : QObject(parent)
{

}

QStringList UiController::irreducibleStrings() const
{
    return m_irreducibleStrings;
}

QStringList UiController::historyStrings() const
{
    return m_historyStrings;
}


QString UiController::mainPolynomialString() const
{
    return m_mainPolynomialString;
}

QString UiController::firstOperandString() const
{
    return m_firstOperandString;
}

QString UiController::secondOperandString() const
{
    return m_secondOperandString;
}

QString UiController::result() const
{
    return m_result;
}

void UiController::setIrreducibleStrings(QStringList irreducibleStrings)
{
    if (m_irreducibleStrings == irreducibleStrings)
        return;

    m_irreducibleStrings = irreducibleStrings;
    emit irreducibleStringsChanged(m_irreducibleStrings);
}

void UiController::setHistoryStrings(QStringList historyStrings)
{
    if (m_historyStrings == historyStrings)
        return;

    m_historyStrings = historyStrings;
    emit historyStringsChanged(m_historyStrings);
}

void UiController::setMainPolynomialString(QString mainPolynomialString)
{
    if (m_mainPolynomialString == mainPolynomialString)
        return;

    m_mainPolynomialString = mainPolynomialString;
    emit mainPolynomialStringChanged(m_mainPolynomialString);
}

void UiController::setFirstOperandString(QString firstOperandString)
{
    if (m_firstOperandString == firstOperandString)
        return;

    m_firstOperandString = firstOperandString;
    emit firstOperandStringChanged(m_firstOperandString);
}

void UiController::setSecondOperandString(QString secondOperandString)
{
    if (m_secondOperandString == secondOperandString)
        return;

    m_secondOperandString = secondOperandString;
    emit secondOperandStringChanged(m_secondOperandString);
}

void UiController::setResult(QString result)
{
    if (m_result == result)
        return;

    m_result = result;
    emit resultChanged(m_result);
}
