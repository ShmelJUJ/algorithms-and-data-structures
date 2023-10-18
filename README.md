[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Js4oAAfY)
# Разбиение числа

Набор положительных чисел a<sub>1</sub>, a<sub>2</sub>, ..., a<sub>k</sub> называется разбиением натурального числа[^1] n, если n = a<sub>1</sub> + a<sub>2</sub> + ... + a<sub>k</sub>, где a<sub>1</sub> ⩾ a<sub>2</sub> ⩾...⩾ a<sub>k</sub> > 0.

Например, существует 5 различных разбиений числа 4:
* 1+1+1+1
* 2+1+1
* 2+2
* 3+1
* 4

Необходимо для заданных чисел n и k вычислить число возможных разбиений n на k частей.

Шаблон программы приведен в файле `partition.cpp`. В нём необходимо написать реализацию функции `partition`.

Числа n и k пользователь вводит с клавиатуры (n, k⩽500). Результатом работы программы является выведенное в консоль число разбиений n на k частей.

### Пример
**Вход:** `4 2`

**Выход:** `2`

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 

[^1]: <https://en.wikipedia.org/wiki/Partition_(number_theory)>

# Игра в пьяницу

В игре в пьяницу карточная колода (52 карты) раздается поровну двум игрокам. 
Игроки не смотрят в свои карты, а кладут их в стопку рядом с собой. 
Далее они вскрывают по одной верхней карте, и тот, чья карта старше, забирает себе обе вскрытые карты, которые кладутся под низ его колоды. 
Тот, кто остается без карт – проигрывает.

## Спор
Если у игроков окажутся одинаковые карты (такая ситуация называется «спор»), то каждый из игроков (сначала первый, потом второй) кладет сверху ещё по одной карте, и тот, чья карта оказалась старше, снимает карты. 

Если у игрока нет карт чтобы провести спор, то он проигрывает.

## Достоинство карт

Достоинство карт (от высших к низшим): A K Q J 10 9 8 7 6 5 4 3 2
 
Туз побеждает короля, король – даму. И так далее, тройки побеждает двойку.

При этом, самая младшая карта `2` побеждает самую старшую карту ("двойка берет туза").

Масти карт (S, H, D, C) роли не играют. 

## Порядок карт

Игрок, который забирает себе карты, сначала кладет под низ своей колоды карту первого игрока, затем карту второго игрока (то есть карта второго игрока оказывается внизу колоды).

Если был «спор», то сначала кладется под низ своей колоды самая первая карта первого игрока, затем карта второго игрока, потом следующая карта первого игрока и т. д.

## Задание

Напишите программу, которая моделирует игру в пьяницу и определяет, кто выигрывает. 

Имена входного и выходного файлов заданы в командной строке. 

## Формат входных данных

Во входном файле записана информация о перетасованной колоде карт (52 карты). 

В каждой отдельной строке входного файла записаны достоинство и масть карты через пробел. Например, тройка треф, семерка червей, туз бубен:
```
3 С
7 H
A D
```
Первые 26 карт отдаются первому игроку, оставшиеся – второму.
Карты перечислены сверху вниз, то есть первая карта из файла должна оказаться первой картой в стопке первого игрока (будет открыта первой). 

## Формат выходных данных
Программа должна определить, кто выигрывает при данной раздаче, и вывести слово 
* `first`, если выигрывает первый игрок, 
* `second`, если выигрывает второй игрок, 
* `draw`, если ничья (в результате спора игроки выложили все свои карты).
 
Если на протяжении 10<sup>6</sup> ходов игра не заканчивается, программа должна вывести слово `unknown`.

## Требования к реализации

Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 


# Задание 2: Очередь с минимумом и максимумом

Реализуйте работу очереди. На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. 
* Команда «+ X» означает добавление в очередь числа X (число по модулю не превышает 10<sup>9</sup>). 
* Команда «−» означает изъятие элемента из очереди. 
* Команда «?» означает поиск максимальной разности (разности между максимальным и минимальным элементами) в очереди.

**Входной файл.** В первой строке содержится N (1 ≤ N ≤ 10<sup>6</sup>) — число команд. В последующих строках содержатся команды, по одной в каждой строке.

**Выходной файл.** Для каждой операции поиска максимальной разности в очереди выведите её результат. Результаты должны быть выведены в том порядке, в котором эти операции встречаются во входном файле. Входные данные гарантируют, что операции извлечения или поиска разности для пустой очереди не производятся.

## Пример
Вызов программы `minmaxqueue queue.in queue.out`

**queue.in**
```
7
+ 1
?
+ 10
?
-
?
-
```

**queue.out**
```
0
9
0
```

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 

# Задание 3: Кандидаты для собеседования
Во время аккредитации эксперту необходимо провести собеседование с обучающимися по образовательной программе. 
Но студентов достаточно много и побеседовать со всеми у эксперта нет возможности, поэтому он попросил учебный отдел выбрать троих представителей: 

* «слабый студент» — студент с самым низким «средним баллом зачетки», 
* «средний студент» — студент с медианным «средним баллом зачетки», 
* «сильный студент» — студент с самым высоким «средним баллом зачётки». 

Считается, что у студента на образовательной программе медианный «средний балл зачётки», если при сортировке студентов по «среднему баллу зачётки» он оказывается ровно посередине списка. 
Известно, что количество студентов нечетное (3 ≤ n ≤ 99999). 

Известно, что у каждого студента есть уникальный идентификационный номер, значение которого расположено в границах от 1 до n. 
Информация о среднем балле зачетки хранится в массиве `M` таким образом, что «средний балл зачётки» студента с идентификационным номером i, содержится в ячейке `M[i]`. 
Помогите сотруднику учебного отдела вычислить идентификационные номера студентов, которые будут приглашены на встречу с экспертом.

### Формат входного файла
Имя входного файла задано в командной строке. 

Первая строка входного файла содержит число студентов n (3 ≤ n ≤ 99999, n нечетно). 

Вторая строка содержит описание массива M, состоящее из n положительных вещественных чисел, разделенных пробелами. 
Гарантируется, что все элементы массива M различны, их значения имеют точность не более двух знаков после запятой.

### Выход
Выведите в консоль три целых положительных числа, разделенных пробелами — идентификационные номера самого слабого, среднего и самого сильного студента.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 


# Задание 4: Число пересечений
Даны отрезки, концы которых имеют целочисленные координаты и один их них (концов) находится на прямой `y=0`, а второй на прямой `y=1`. 

Найти количество пар пересекающихся отрезков.

Имя входного файла с информацией об отрезках задано в командной строке. Ответ необходимо вывести в консоль.

### Формат входного файла
В первой строке входного файла содержится число n (1 ≤ n ≤ 1 000 000) — число отрезков. 

Во второй строке и далее находятся пары целых чисел: координата `x` начала отрезка (точка на прямой `y=0`) и координата `x` конца отрезка (точка на прямой `y=1`).

### Выход
Выведите в консоль количество пар пересекающихся отрезков.


## Пример
![Пример](img.png)

```
8
2 2
4 3
1 4
5 5
6 6
7 6
8 7
8 8
```
Ответ: `4` 

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 


# Задание 5: K-ые порядковые статистики

Элементы массива получаются по рекуррентной формуле: x<sub>i</sub> = A·x<sub>i-2</sub> + B·x<sub>i-1</sub> + C, i=3,4,… 

В массиве из n элементов нужно найти k<sub>1</sub>-ое, (k<sub>1</sub> + 1)-ое, …, k<sub>2</sub>-ое в порядке возрастания в этом массиве.

## Формат входного файла
В первой строке входного файла содержатся три числа: размер массива n, и границы интервала k<sub>1</sub> и k<sub>2</sub> (2 ≤ n ≤ 10<sup>8</sup>, 1 ≤ k<sub>1</sub> < k<sub>2</sub> ≤ n, k<sub>2</sub> − k<sub>1</sub> < 200). 

Во второй строке находятся числа A, B, C, x<sub>1</sub>, x<sub>2</sub> по модулю не превосходящие 10<sup>9</sup>. 

Вычисления элементов массива по формуле должны производится в 32-битном знаковом типе (тип данных `int`), переполнения должны игнорироваться.

## Формат выходного файла
В единственной строке выходного файла выведите k<sub>1</sub>-е, (k<sub>1</sub> + 1)-ое, …, k<sub>2</sub>-е в порядке возрастания числа в массиве. Числа разделяйте одним пробелом.

Имена входного и выходного файла задаются в командной строке.

## Примеры
1. Входной файл:
```
5 3 4
2 3 5 1 2
```
Выходной файл:
```
13 48
```

2. Входной файл:
```
5 3 4
200000 300000 5 1 2
```
Выходной файл:
```
2 800005
```
Во втором примере элементы массива равны: `(1, 2, 800005, −516268571, 1331571109)`.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 

# Задание 6: Генератор одноразовых паролей
Представьте себе, что вы оказались по работе в командировке в чужом городе, и у вас сломались и ноутбук и смартфон, или их и не было, 
а вам срочно понадобилось зайти в корпоративную почту или получить доступ на корпоративный портал. Что делать? 
Большинство из нас пойдёт в место общего пользования интернетом. Но работать за чужим компьютером не безопасно, так как нет гарантии, что на нём не установлен кейлогер, например.
Если на страничке аутентификации ввести логин и пароль, то нет гарантия того, что они тут же не попадут в руки третьих лиц. 
Что же делать? Эту проблему помогают решить одноразовые пароли. Вы вводите логин, вводите одноразовый пароль, и получаете доступ к необходимому ресурсу. 
Но где взять одноразовые пароли? Нужен генератор одноразовых паролей.

В организации решили хранить все пароли в текстовом файле, а чтобы определить конкретный одноразовый пароль пользователю надо будет просто сделать несколько фаз LSD-сортровки.

Вам необходимо написать генератор одноразовых паролей.

Имена входного и выходного файла заданы аргументами командной строки.

## Формат входного файла
В первой строке входного файла содержится число `N` — число строк, число `M` — их длина, число `K` – число фаз цифровой сортировки (1 ≤ N ≤ 10<sup>6</sup>, 1 ≤ K ≤ M ≤ 10<sup>6</sup>). 

Далее, начиная со второй строки файла, по вертикали записаны строки, то есть вторая строка файла состоит из первых символов `N` строк, третья строка файла состоит из вторых символов `N` строк и т.д.

## Формат выходного файла
В первой строке необходимо вывести строку из первых символов исходных строк после `K` фаз цифровой сортировки по младшему разряду (LCD-сортировка, Least Significant Digit radix sort).

## Примеры
В примерах даны три строки:
1. `abbb`
2. `caba`
3. `bbaa`

### Пример 1
input.txt
```
3 4 1
acb
bab
bba
baa
```
output.txt
```
cba
```
*Примечание.* Первая фаза цифровой сортировки отсортирует строки по последнему символу, таким образом, первой строкой окажется «caba» (столбик 2), затем «bbaa» (столбик 3), затем «abbb» (столбик 1). 
Таким образом, ответ равен «cba» (первый символ из столбца 2, первый символ из столбца 3, первый символ столбца 1).

### Пример 2
input.txt
```
3 4 2
acb
bab
bba
baa
```
output.txt
```
bca
```

### Пример 3
input.txt
```
3 4 3
acb
bab
bba
baa
```
output.txt
```
cba
```

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 

# Задание 7: AA-Tree

Реализовать контейнер множество с помощью самобалансирующегося AA-дерева.

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. 
* Команда «+ X» означает добавление в множество числа X, по модулю не превышающего 10<sup>9</sup>. 
* Команда «− X» означает изъятие элемента из множества. 
* Команда «? X» означает проверку наличия числа X в множестве.

## Входной файл
В первой строке содержится N (1 ≤ N ≤ 10<sup>6</sup>) — число команд. В последующих строках содержатся команды, по одной в каждой строке.

## Выходной файл
* Для каждой операции «+ X» или «– X» вывести баланс корня дерева после выполнения операции. Если дерево пустое (в нем нет вершин), вывести 0. 
* Для каждой операции «? X» вывести её результат: true, если ключ есть в множестве, false – иначе. 
* Результаты должны быть выведены в том порядке, в котором эти операции встречаются во входном файле. 
* Вывод для каждой операции должен содержаться в отдельной строке.

Имена входного и выходного файла задаются в командной строке.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 

# Задание 8: Проверка индекса

Для построения индекса использовалось B-дерево.
В результате ошибки индекс мог быть поврежден. 
В файл выгрузили дамп B-дерева. 
Нужно проверить по выгруженной информации правильно ли построен индекс (выполняются ли все свойства B-дерева). Ключи, хранимые в дереве, являются целыми числами (int).

Имя входного файла (с дампом B-дерева) задано в командной строке.

## Входной файл
В первой строке файла содержится три числа: 

* N — число узлов B-дерева,
* t — параметр дерева, не меньший 2,
* root — номер узла (адрес), который является корнем дерева.

В последующих N строках содержатся описания узлов дерева.

Для листьев описание имеет вид:
```
leaf: 0xномер_узла (количество_ключей: ключ1 ключ2 ...)
```
В начале строки идет `leaf: 0x`, далее указан номер узла, пробел, в круглых скобках записано число элементов в узле, двоеточие и перечислены значения ключей (целые числа).

Для внутренних узлов (не листьев) описание имеет вид:
```
branch: 0xномер_узла (количество_ключей: ключ_1 ключ_2 ...) (количество_потомков: номер_узла_1 номер_узла_2 номер_узла_3 ...)
```
В начале строки идет `branch: 0x`, далее указан номер узла, пробел, в первых круглых скобках записано число элементов в узле, двоеточие и перечислены значения ключей (целые числа), во вторых круглых скобках указано число потомков узла, двоеточие и перечислены номера узлов-потомков.

Номера узлов — это беззнаковые целые числа.

## Вывод
В консоль вывести слово `yes`, если во входном файле правильное B-дерево, иначе вывести `no`.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 



# Задание 9: Хэш-таблица
Реализовать контейнер множество с помощью хэш-таблицы, поддерживающий операции «добавление ключа», «удаление ключа», «проверка существования ключа».

На вход программе подаются строки, содержащие команды. Каждая строка содержит одну команду. 
* Команда «+ X» означает добавление в множество числа X, по модулю не превышающего 10<sup>9</sup>. 
* Команда «− X» означает изъятие элемента из множества. 
* Команда «? X» означает проверку наличия ключа X в множестве.

## Входной файл
В первой строке содержится N (1 ≤ N ≤ 10<sup>6</sup>) — число команд. В последующих строках содержатся команды, по одной в каждой строке.

## Выходной файл
* Для каждой операции «? Х» вывести её результат: true, если ключ есть в множестве, false – иначе. 
* Результаты должны быть выведены в том порядке, в котором эти операции встречаются во входном файле. 
* Вывод для каждой операции должен содержаться в отдельной строке.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 


# Задание 10: Очередь с приоритетами

Реализуйте очередь с приоритетами. Очередь должна поддерживать следующие операции: 
* добавить элемент, 
* извлечь минимальный элемент, 
* уменьшить элемент, добавленный во время одной из операций.

Все операции нумеруются по порядку, начиная с единицы. Гарантируется, что число команд, а также и размер очереди в процессе выполнения команд, не превысит 10<sup>5</sup>.

## Формат входного файла
Входной файл содержит описание операций с очередью. Операции могут быть следующими:
* `push x` — требуется добавить элемент x в очередь;
* `extract-min` — требуется удалить из очереди минимальный элемент и вывести его в выходной файл. Если очередь пуста, в выходной файл требуется вывести звездочку `*`;
* `decrease-key x y` — требуется заменить значение элемента, добавленного в очередь операцией `push` в строке входного файла номер `x`, на `y`. Гарантируется, что на строке `x` действительно находится операция `push`, что этот элемент не был ранее удален операцией `extract-min`, и что `y` меньше, чем предыдущее значение этого элемента.

В очередь помещаются и извлекаются только целые числа, не превышающие по модулю 10<sup>9</sup>.

## Формат выходного файла
Выведите последовательно результат выполнения всех операций `extract-min`, по одному в каждой строке выходного файла. Если перед очередной операцией `extract-min` очередь пуста, выведите вместо числа звездочку `*`.

## Пример
**input.txt**
```
push 3
push 4
push 2
extract-min
decrease-key 2 1
extract-min
extract-min
extract-min
```

**output.txt**
```
2
1
3
*
```

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 


# Задание 11: Минимальное остовное дерево
Вычислить вес минимального остовного дерева обыкновенного графа.

Имя входного файла с графом задано в командной строке. Ответ (вес минимального остова) вывести в консоль.

## Формат входного файла
В первой строке файла содержится два натуральных числа: количество вершин и количество ребер графа.

В последующих строках содержатся описания ребер: начальная вершина ребра, конечная вершина ребра, вес ребра.

Нумерация вершин начинается с 0. Веса ребер — целые числа.

## Вывод
Вывести целое число (вес минимального остовного дерева графа) в консоль.

## Требования к реализации
Программа не должна использовать контейнеры STL (std::vector, std::string и т. д.). 

