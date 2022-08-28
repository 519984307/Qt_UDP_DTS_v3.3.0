#include "webclass.h"

WebClass::WebClass(QObject *parent) : QObject(parent)
{

}

void WebClass::jscallme()
{
      QMessageBox::information(NULL, "jscallme", m_content);
}
