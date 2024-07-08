Наш проект - Silicon Valley Bank 2 потому, что первый обанкротился.
В папке site/api лежит Local_Sil_Valley_Bank.exe и Local_Sil_Valley_Bank_Console.exe.
Local_Sil_Valley_Bank.exe - файл с api для доступа к функциям приложения, этот файл использует
php скрипт для вывода данных на сайте.

Local_Sil_Valley_Bank_Console.exe - файл с консольным интерфейсом к приложению.

Чтобы сайт работал необходимо скачать MySQL (https://dev.mysql.com/downloads/installer/)
и Веб сервер Apache(https://www.apachefriends.org/download.html).
В папке установленного XAMPP (Apache + PHP) в директории apache/conf лежит файл httpd.conf
примерно на 252-253 строках необходимо изменить путь по которому apache будет искать файлы
сайта. Тут необходимо указать путь до "папка с репозиторием"/site.
Пример:
DocumentRoot "C:\Users\vladb\source\repos\reserve_silicon_valley_bank_2\site"
<Directory "C:\Users\vladb\source\repos\reserve_silicon_valley_bank_2\site">

После нужно в панели XAMPP запустить Apache.

Чтобы MySQL заработал как надо, необходимо в консоли cmd.exe зайти в папку с репозиторием,
в ней лежит файл siliconDB.sql - это файл с объявлениями базы данных. После того как зашли
в папку с репозиторием, необходимо выполнить команду mysql -u root -p < siliconDB.sql
она должна перенести объявления из файла в СУБД MySQL (если не получилось попробуйте добавить
папку с исполняемыми файлами MySQL в переменную PATH
(путь до папки C:/Program Files/MySQL/MySQL Server 8.0/bin/)
).

Теперь все должно работать. Можно написать в поисковой строке браузера localhost и увидишь
сайт с проектом.

P.S. У нас в файле UML нет классов Command... которые реализуют паттерн Команда, он используется
для доступа к базе данных. Мы не смогли их добавить потому, что закончился триал на нашей
рисовалке для UML.