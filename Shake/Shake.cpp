#include "Shake.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) { // Исправлено с Strind на String
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Shake::Shake form;
    Application::Run(% form); // Удалены лишние пробелы и добавлена точка с запятой
    return 0; // Возвращаем 0 для завершения программы
}
