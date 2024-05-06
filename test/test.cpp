#include <QString>
#include <QDebug>

int main() {
    QString str = "/Users/polzovatel/work/aqsi_proj/TerminalInstallerApp/installerAppForMac_0.1";
    QChar sim = '/'; // Замените 'н' на нужный символ

    int index = str.lastIndexOf(sim);
    if (index != -1) {
        str = str.left(index + 1); // +1, чтобы включить сам нужный символ
    }

    qDebug() << str; // Выведет: "Пример строки с нужным символом"

    return 0;
}