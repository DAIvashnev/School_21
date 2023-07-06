# Операционные системы UNIX/Linux (Базовый).

Установка и обновления системы Linux. Основы администрирования.


## Contents
1. [Задание 1](#задание-1)
2. [Задание 2](#задание-2)
3. [Задание 3](#задание-3)
4. [Задание 4](#задание-4)
5. [Задание 5](#задание-5)
6. [Задание 6](#задание-6)
7. [Задание 7](#задание-7)
8. [Задание 8](#задание-8)
9. [Задание 9](#задание-9)
10. [Задание 10](#задание-10)
11. [Задание 11](#задание-11)
12. [Задание 12](#задание-12)
13. [Задание 13](#задание-13)
14. [Задание 14](#задание-14)
15. [Задание 15](#задание-15)


## Задание 1
+ Скачиваем VirtualBox и образ iso для ubuntu-server

    Проходим базовую конфигурацию виртуальной машины, создаем пользователя и все готово!

+ Выполняем команду cat /etc/issue

    | ![](img/1.Install_VB_Ubuntu.png) |
    |:--:|
    | *скрин поставленной версии* |

## Задание 2
+ создаем нового пользователя добавляя его в группу adm

    | ![](img/2.Useradd.png) |
    |:--:|
    | *команда добавления пользователя* |
+ проверим наличие пользователя

    | ![](img/2.1.png) |
    |:--:|
    | *вывод команды cat /etc/passwd* |

## Задание 3
+ задаем имя машины изменив содержимое файла /etc/hostname на user-1

    | ![](img/3.Hostname.png) |
    |:--:|
    | *вывод команды hostname* |
+ установим временную зону для Москвы

    | ![](img/3.1.TimeDate.png) |
    |:--:|
    | *вывод команды date* |
+ выведем список сетевых интерфейсов

    | ![](img/3.2.lo.png) |
    |:--:|
    | *сетевые интерфейсы нашей системы* |

    lo - Это локальный интерфейс, который позволяет программам обращаться к этому компьютеру
    
    enp0s3 - Сетевой интерфейс проводного интернета Ethernet
+ получаем ip адрес от DHCP сервера

    | ![](img/3.3.dhcp.png) |
    |:--:|
    | *ip адрес полученный от DHCP* |

    DHCP - Dynamic Host Configuration Protocol (протокол автоматизации назначения IP-адреса клиенту)
+ Выводим ip и gateway по умолчанию

    | ![](img/3.4.default.png) |
    |:--:|
    | *вывод команды ip route* |
+ Чтобы задать статичные настройки (ip, gw, dns) нужно поменять конфигурацию файла /etc/netplan/00-installer-config.yaml<br>Отключаем динамическое получение ip и пишем свои настройки

    | ![](img/3.5.addresses.png) |
    |:--:|
    | *статические настройки* |
+ Применим изменения и перезагрузим машину, посмотрим изменились ли ip и пропингуем 1.1.1.1 и ya.ru

    | ![](img/3.6.Route.png) |
    |:--:|
    | *настройки поменялись* |

    | ![](img/3.7.Ping.png) |
    |:--:|
    | *пингуем ya.ru* |

    | ![](img/3.7.Ping1.png) |
    |:--:|
    | *пингуем 1.1.1.1* |

## Задание 4
+ Обновляем все пакеты командой sudo apt full-upgrade

    | ![](img/4.Update.png) |
    |:--:|
    | *Обновлений больше нет* |


## Задание 5
+ Назначение команды для администрирования sudo - выполнять команды от имени других пользователей (чаще всего от суперпользователя)

+ Для того чтобы созданный юзер мог выполнять команду sudo, его надо добавить в группу sudo

    | ![](img/5.Usermod.png) |
    |:--:|
    | *добавление пользователя в группу sudo* |

+ Теперь от его имени можно поменять hostname

    | ![](img/5.1.HostRename.png) |
    |:--:|
    | *редактируем файл от имени другого пользователя* |

    | ![](img/5.2.NewHost.png) |
    |:--:|
    | *новый hostname* |

## Задание 6
+ Служба автоматической синхронизации времени была настроена еще в 3 шаге

    | ![](img/6.LocalTime.png) |
    |:--:|
    | *Вывод часового пояса* |

    | ![](img/6.1.TimeShow.png) |
    |:--:|
    | *Вывод команды timedatectl show* |

## Задание 7
+ Были установлены редакторы: VIM, Nano, Joe

+ ### VIM
    + Для выхода с сохранением **:wq**

        | ![](img/7.TestVim.png) |
        |:--:|
        | *Содержимое перед закрытием* |
    + Для выхода без сохранения **:q!**

        | ![](img/7.1TestVim.png) |
        |:--:|
        | *Содержимое после редактирования* |
    + Для поиска с заменой всех вхождений **:%s/<то что ищем>/<замена>/g**

        | ![](img/7.2.TestVim.png) |
        |:--:|
        | *Команда для поиска с заменой* |

        | ![](img/7.3.TestVim.png) |
        |:--:|
        | *Содержимое после команды* |

+ ### Joe
    + Для выхода с сохранением **ctrl K** затем **X**

        | ![](img/7.4TestJoe.png) |
        |:--:|
        | *Содержимое перед закрытием* |
    + Для выхода без сохранения **ctrl K** затем **Q** и не сохранять изменения

        | ![](img/7.5.TestJoe.png) |
        |:--:|
        | *Содержимое после редактирования* |
    + Для поиска с заменой всех вхождений **ctrl G** затем **R**
        | ![](img/7.6.TestJoe.png) |
        |:--:|
        | *Команда для поиска* |

        | ![](img/7.7.TestJoe.png) |
        |:--:|
        | *Команда для замены* |

        | ![](img/7.8.TestJoe.png) |
        |:--:|
        | *Содержимое после команды* |

+ ### Nano
    + Для выхода с сохранением **ctrl X** и соглашаемся сохранить изменения

        | ![](img/7.9.TestNano.png) |
        |:--:|
        | *Содержимое перед закрытием* |
    + Для выхода без сохранения **ctrl X** и не соглашаемся сохранить изменения
        | ![](img/7.10TestNano.png) |
        |:--:|
        | *Содержимое после редактирования* |
    + Для поиска с заменой всех вхождений **ctrl W** затем **ctrl R**
        | ![](img/7.11.TestNano.png) |
        |:--:|
        | *Команда для поиска* |

        | ![](img/7.12.TestNano.png) |
        |:--:|
        | *Команда для замены* |

        | ![](img/7.13.TestNano.png) |
        |:--:|
        | *Содержимое после команды* |

## Задание 8
+ Для установки SSHd введем **sudo apt install openssh-server**

+ Чтобы добавить автостарт службы при загрузке системы введем **sudo systemctl enable ssh**

+ Для переназначения порта изменим порт в файле /etc/ssh/sshd_config на 2022 и разкомментим его

+ Используем команду ps с ключами -ef для того чтобы увидеть подробную информацию по всем процессам и отберем только sshd

    | ![](img/8.ps.png) |
    |:--:|
    | *вывод процессов sshd* |

+ Перезапустим и введем команду **netstat -tan**

    | ![](img/8.1.Nenstat.png) |
    |:--:|
    | *вывод команды* |

    ключи:

    + -ta Комбинация выводит список всех tcp портов (как прослушиваемых, так и нет)
    + -n Отображает адреса и номера портов в числовом формате

    Столбцы:

    + Proto – протокол
    + Recv-Q – количество байтов, помещённых в буфер приёма TCP/IP, но не переданных приложению
    + Send-Q – количество байтов, помещённых в буфер отправки TCP/IP, но не отправленных, или отправленных, но не подтверждённых
    + Local Address – локальный адрес сервера. Так 0.0.0.0:port – значит подключаться можно ко всем адресам сервера
    + Foreign Address – адрес второй стороны. Так 0.0.0.0:* – значит подключаться можно с любых адресов и с любых портов
    + State – состояние подключения, или прослушивания

## Задание 9
+ Запустим команду top

    | ![](img/9.Top.png) |
    |:--:|
    | *вывод команды* |

    Что мы можем узнать из этого вывода?

    + uptime - 15:56:13 up 1:25 min
    + количество авторизованных пользователей - 1 user
    + общую загрузку системы - 0.0 (0%)
    + общее количество процессов - 97
    + загрузку cpu - (0.0% системные процессы) (99.7% процент времени, когда ЦПУ не был загружен)
    + загрузку памяти 214.3 Mb
    + pid процесса занимающего больше всего памяти - 1293
    
        | ![](img/9.1.Pid.png) |
        |:--:|
        | *Shift+M, чтобы отсортировать вывод команды top по памяти* |
    
    + pid процесса, занимающего больше всего процессорного времени - 671
    
        | ![](img/9.1.Pid.png) |
        |:--:|
        | *Shift+F, чтобы войти в интерактивный режим и выбрать поле TIME+* |

+ Запустим команду htop

    + сортировка по PID, PERCENT_CPU, PERCENT_MEM, TIME
        | ![](img/9.3.s1.png) |
        |:--:|
        | *Sort_by PID* |
        | ![](img/9.4.s2.png) |
        | *Sort_by PERCENT_CPU* |
        | ![](img/9.5.s3.png) |
        | *Sort_by PERCENT_MEM* |
        | ![](img/9.6.s4.png) |
        | *Sort_by TIME* |
    + фильтрация для процесса sshd
        | ![](img/9.7.Filtr.png) |
        |:--:|
        | *Фильтрация sshd* |
    + процесс syslog, найденный, используя поиск
        | ![](img/9.8.Search.png) |
        |:--:|
        | *поиск по syslog* |
    + добавим вывод hostname, clock и uptime
        | ![](img/9.9.Add.png) |
        |:--:|
        | *Вывод основной информации системы* |

## Задание 10
+ Запустим команду fdisk -l
    | ![](img/10.Disk.png) |
    |:--:|
    | *Вывод информации по диску* |

    + название жесткого диска - /dev/sda
    + размер - 30G
    + количество секторов - 63393664
    + размер swap - 2.9G
        | ![](img/10.1.Swap.png) |
        |:--:|
        | *размер swap* |

## Задание 11
+ Запустим команду df -h (размер без флага -h в килобайтах)
    | ![](img/11.Df.png) |
    |:--:|
    | *Вывод команды df* |
    
    Для корневого раздела(/):
    + размер раздела - 14G
    + размер занятого пространства - 5.5G
    + размер свободного пространства - 7.7G
    + процент использования - 42%

+ Запустим команду df -Th
    | ![](img/11.1.Df.png) |
    |:--:|
    | *Вывод команды df* |
    
    Для корневого раздела(/):
    + размер раздела - 14G
    + размер занятого пространства - 5.5G
    + размер свободного пространства - 7.7G
    + процент использования - 42%
    + тип файловой системы - ext4

## Задание 12
+ Выведем размер папок /home, /var, /var/log и всего содержимого в /var/log
    | ![](img/12.Du.png) |
    |:--:|
    | *вывод команды du* |
    | ![](img/12.1.Home.png) |
    | *размер /home* |
    | ![](img/12.2.Var.png) |
    | *размер /var* |
    | ![](img/12.3.Var_log.png) |
    | *размер /var/log* |
    | ![](img/12.4.Full.png) |
    | *размер всего содержимого в /var/log* |

## Задание 13
+ Установим ncdu и выведем размер папок из прошлого задания
    | ![](img/13.Home.png)_ ![](img/13.1.Var.png)_ ![](img/13.2.Var_log.png) |
    |:--:|
    | *вывод размера папок с помощью команды ncdu* |

## Задание 14
+ Для того чтобы посмотреть время последней успешной авторизации, имя пользователя и метод входа в систему, нужно открыть файл /var/log/auth.log
    | ![](img/14.log.png) |
    |:--:|
    | *логи авторизации* |

    Видим время, имя пользователя и метод входа в систему (by enedinae)

+ Перезапускаем службу sshd командой **sudo systemctl restart ssh** и находим информацию о перезапуске в файле /var/log/syslog
    | ![](img/14.1.Restart_ssh.png) |
    |:--:|
    | *логи syslog* |

    Также информацию о перезапуске можно найти в логах авторизации
    | ![](img/14.2.Log_auth.png) |
    |:--:|
    | *логи авторизации* |

## Задание 15
+ Задаем для планировщика выполнение скрипта и ждем пару минут, затем смотрим выполнилось ли в логах /var/log/syslog
    | ![](img/15.Cron.png) |
    |:--:|
    | *логи syslog* |

+ посмотрим список текущих задач для CRON
    | ![](img/15.1.cron-l.png) |
    |:--:|
    | *список задач* |

+ удалим все задачи и посмотрим на список снова
    | ![](img/15.2.Del.png) |
    |:--:|
    | *список задач* |