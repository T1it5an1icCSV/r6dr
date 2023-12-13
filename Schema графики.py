import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# загрузка данных из csv-файла
data = pd.read_csv('titanic.csv')

# линейный график
# Создадим график, на котором будет отображена зависимость количества выживших от возраста
plt.figure(figsize=(10, 6))
sns.lineplot(data=data, x='age', y='survived')
plt.title('Number of Survivors by Age')
plt.xlabel('Age')
plt.ylabel('Number of Survivors')
plt.show()

# Создадим график, на котором будет отображена зависимость количества пассажиров в разных классах от времени
plt.figure(figsize=(10, 6))
sns.lineplot(data=data, x='age', y='pclass')
plt.title('Number of Passengers by Age and Class')
plt.xlabel('Age')
plt.ylabel('Passenger Class')
plt.show()

# Создадим график, на котором будет отображена зависимость выживаемости от количества родственников на борту
plt.figure(figsize=(10, 6))
sns.lineplot(data=data, x='sibsp', y='survived')
plt.title('Survival Rate by Number of Siblings/Spouses')
plt.xlabel('Number of Siblings/Spouses')
plt.ylabel('Survival Rate')
plt.show()

# столбчатая диаграмма
# Создадим график, на котором будет отображено количество выживших и погибших пассажиров по полу
plt.figure(figsize=(10, 6))
sns.countplot(data=data, x='sex', hue='survived')
plt.title('Number of Survivors and Victims by Gender')
plt.xlabel('Gender')
plt.ylabel('Count')
plt.show()

# Создадим график, на котором будет отображено количество пассажиров в разных классах
plt.figure(figsize=(10, 6))
sns.countplot(data=data, x='pclass')
plt.title('Number of Passengers by Class')
plt.xlabel('Class')
plt.ylabel('Count')
plt.show()

# Создадим график, на котором будет отображено количество пассажиров в разных возрастных группах
plt.figure(figsize=(10, 6))
data['age_group'] = pd.cut(data['age'], bins=[0, 18, 35, 60, 100])
sns.countplot(data=data, x='age_group')
plt.title('Number of Passengers by Age Group')
plt.xlabel('Age Group')
plt.ylabel('Count')
plt.show()

# круговая диаграмма
# Создадим круговую диаграмму, на которой будет отображена доля выживших и погибших
survived_counts = data['survived'].value_counts()
labels = ['Victims', 'Survivors']
plt.figure(figsize=(10, 6))
plt.pie(survived_counts, labels=labels, autopct='%1.1f%%')
plt.title('Survivors vs Victims')
plt.show()

# Создадим круговую диаграмму, на которой будет отображена доля пассажиров разных полов
gender_counts = data['sex'].value_counts()
labels = list(gender_counts.index)
plt.figure(figsize=(10, 6))
plt.pie(gender_counts, labels=labels, autopct='%1.1f%%')
plt.title('Passenger Gender Distribution')
plt.show()

# диаграмма рассеяния
# Создадим диаграмму рассеяния, на которой будет отображена зависимость выживаемости от возраста и пола
plt.figure(figsize=(10, 6))
sns.scatterplot(data=data, x='age', y='sex', hue='survived')
plt.title('Survival Rate by Age and Gender')
plt.xlabel('Age')
plt.ylabel('Gender')
plt.show()

# Создадим диаграмму рассеяния, на которой будет отображена зависимость стоимости билета от возраста
plt.figure(figsize=(10, 6))
sns.scatterplot(data=data, x='age', y='fare')
plt.title('Ticket Fare by Age')
plt.xlabel('Age')
plt.ylabel('Fare')
plt.show()

# гистограмма
# Создадим гистограмму, на которой будет отображено распределение возрастов пассажиров
plt.figure(figsize=(10, 6))
sns.histplot(data=data, x='age', bins=20)
plt.title('Age Distribution of Passengers')
plt.xlabel('Age')
plt.ylabel('Count')
plt.show()

# Создадим гистограмму, на которой будет отображено распределение стоимости билетов
plt.figure(figsize=(10, 6))
sns.histplot(data=data, x='fare', bins=20)
plt.title('Ticket Fare Distribution')
plt.xlabel('Fare')
plt.ylabel('Count')
plt.show()

# Создадим гистограмму, на которой будет отображено распределение количества родственников на борту
plt.figure(figsize=(10, 6))
sns.histplot(data=data, x='sibsp', bins=20)
plt.title('Number of Siblings/Spouses Distribution')
plt.xlabel('Number of Siblings/Spouses')
plt.ylabel('Count')
plt.show()

# Выводы:
# - Из линейных графиков можно сделать вывод, что возраст и класс имеют влияние на выживаемость пассажиров. Молодые пассажиры и те, кто путешествовал в первом классе, имели более высокую выживаемость.
# - Из столбчатых диаграмм можно увидеть, что количество выживших женщин было значительно больше, чем количество выживших мужчин. Также большинство пассажиров путешествовали в третьем классе.
# - Из круговых диаграмм можно сделать вывод, что около 38% пассажиров выжили, а 62% погибли. Пассажиров женского пола было примерно 36%, а мужского - 64%.
# - Из диаграмм рассеяния можно видеть, что большинство выживших имели возраст от 20 до 30 лет, и они были женского пола. Также можно заметить зависимость между стоимостью билета и возрастом, где более дорогие билеты чаще приобретали взрослые пассажиры.
# - Из гистограмм можно сделать выводы о распределении возраста пассажиров, стоимости билетов и количества родственников на борту. Например, можно заметить, что большинство пассажиров были в возрасте от 20 до 30 лет, большинство билетов стоили менее $50, и у большинства пассажиров не было родственников на борту.
