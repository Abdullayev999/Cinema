#include<iostream>
#include<iomanip>
#include<utility>

using namespace std;
/*  Задание 1:

1. Создайте структуру Cinema (название, жанр, рейтинг)
 2. Создайте массив структур Cinema (не менее 3 фильмов)
3. Напишите функцию печати списка всех фильмов
 4. Напишите функцию печати всех фильмов по заданному жанру
5. Реализуйте возможность повышать/понижать рейтинг фильма
6. Реализуйте возможность сортировать фильмы по рейтингу
		(убывание и возрастание). [Для сортировки используйте
		одну реализацию и указатель на функцию для задания критерия
		 сортировки]
*/

struct Cinema
{
	char nameOfMovie[20];
	char genreOfMovie[20];
	int ratingOfMovie;
};


void printListOfMovie(const Cinema* arr, const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << i << '\t' << arr[i].nameOfMovie << "\t\t\t\t";
		cout << arr[i].genreOfMovie << "\t\t\t\t";
		cout << arr[i].ratingOfMovie << endl;
	}
}


void printratingOfMovie(const Cinema arr[], const int size, char ch[])
{
	bool searchMovie = true;

	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(ch, arr[i].genreOfMovie) == 0)
		{
			searchMovie = false;
			cout << arr[i].nameOfMovie << "\t\t\t\t";
			cout << arr[i].genreOfMovie << "\t\t\t\t";
			cout << arr[i].ratingOfMovie << endl;
		}
	}
	if (searchMovie)
	{
		cout << "x\tx\t\t\t\tx\t\t\t\tx\n\n";
		cout << "There are no films for this genre\n";
	}
}


bool up(const int numOne, const int numTwo)
{
	return numOne < numTwo;
}

bool down(const int numOne, const int numTwo)
{
	return numOne > numTwo;
}

typedef bool (*func_ptr)(int, int);

void sortByRating(Cinema*& arr, const int size, const func_ptr box)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i + 1; j < size; j++)
		{
			if (box(arr[i].ratingOfMovie, arr[j].ratingOfMovie))
			{
				swap(arr[i], arr[j]);
			}
		}
	}
}


void deleteOneMovieInArr(Cinema*& arr, int& size, int num)
{
	Cinema* tmp = new Cinema[size - 1];
	for (size_t i = 0, b = 0; i < size; i++)
	{
		if (i != num)
		{
			tmp[b] = arr[i];
			b++;
		}
	}
	size--;
	delete[] arr;
	arr = tmp;
}

enum { Exit, Add, PrintOfList, SearchByGenre, ChangeRating, SortByRating, deleteOneMovie };

int main()
{
	const int ComeBack = -1;
	const int sortDown = 1;
	const int sortUp = 2;

	int raiting;
	int deleteMovie;
	int act;
	int action;
	int quantityMovie;
	char genre[20];

	cout << "Enter quantity movie \n";
	cin >> quantityMovie;

	Cinema* arr = new Cinema[quantityMovie];

	for (size_t i = 0; i < quantityMovie; i++)
	{
		cout << "Enter name of movie \n";
		cin >> arr[i].nameOfMovie;

		cout << "Enter name of genre \n";
		cin >> arr[i].genreOfMovie;

		cout << "Enter name of rating \n";
		cin >> arr[i].ratingOfMovie;
	}

	do
	{
		cout << R"(
Choose an action

0 - Exit
1 - Add movie
2 - Print movie list
3 - Search by genre
4 - Change Rating
5 - Sort movies by rating
6 - Delete movie

)";

		cin >> action;

		if (action == Exit)
		{
			cout << "You have left the program\n";
			break;
		}
		else if (action == Add)
		{
			Cinema* add = new Cinema[quantityMovie + 1];

			for (size_t i = 0; i < quantityMovie; i++)
			{
				add[i] = arr[i];
			}

			cout << "Enter name of movie \n";
			cin >> add[quantityMovie].nameOfMovie;

			cout << "Enter name of genre \n";
			cin >> add[quantityMovie].genreOfMovie;

			cout << "Enter name of rating \n";
			cin >> add[quantityMovie].ratingOfMovie;
			delete[] arr;
			quantityMovie++;
			arr = add;
		}
		else if (action == PrintOfList)
		{
			cout << "\nPrint list of Movies\n\n";
			cout << "#\tName\t\t\t\tGenre\t\t\t\tRating\t\n\n";

			printListOfMovie(arr, quantityMovie);
		}
		else if (action == SearchByGenre)
		{
			cout << "Search by genre\n";
			cin >> genre;

			cout << "\nPrint list of Movies on genre \n\n";
			cout << "\n#\tName\t\t\t\tGenre\t\t\t\tRating\n\n";

			printratingOfMovie(arr, quantityMovie, genre);

		}
		else if (action == ChangeRating)
		{
			int num;
			do
			{
				cout << "Come back  -1\nWrite the movie number( # ) :\n";
				cin >> num;
				if (num < quantityMovie && num >= 0)
				{
					cout << "\n#\tName\t\t\t\tGenre\t\t\t\tRating\n\n";
					cout << num << '\t' << arr[num].nameOfMovie << "\t\t\t\t";
					cout << arr[num].genreOfMovie << "\t\t\t\t";
					cout << arr[num].ratingOfMovie << endl;

					cout << "Please change rating\n";

					cin >> raiting;
					arr[num].ratingOfMovie = raiting;

					cout << "Rating changed\n";

					cout << "\n#\tName\t\t\t\tGenre\t\t\t\tRating\n\n";
					cout << num << '\t' << arr[num].nameOfMovie << "\t\t\t\t";
					cout << arr[num].genreOfMovie << "\t\t\t\t";
					cout << arr[num].ratingOfMovie << endl;
					break;
				}
				else if (num == ComeBack) {
					cout << "You come back\n";
					break;
				}
				else {
					cout << "\nno such number ( # )! \n Try again\n\n";
				}

			} while (true);
		}
		else if (action == SortByRating)
		{
			cout << "\nSort by Rating\n";

			do
			{
				cout << "1  -  Up\n2  -  Down\n\n";
				cin >> act;

				if (act == sortUp)
				{
					sortByRating(arr, quantityMovie, up);
					break;
				}
				else if (act == sortDown)
				{
					sortByRating(arr, quantityMovie, down);
					break;
				}

				else {
					cout << "Wrong selection, try again\n";
				}
			} while (true);

			cout << "\n#\tName\t\t\t\tGenre\t\t\t\tRating\n\n";
			printListOfMovie(arr, quantityMovie);

		}
		else if (action == deleteOneMovie)
		{
			do
			{
				cout << "\nWrite the movie number( # ) for delete  :\n";
				cin >> deleteMovie;
				if (deleteMovie < quantityMovie && deleteMovie >= 0)
				{
					deleteOneMovieInArr(arr, quantityMovie, deleteMovie);
					break;
				}
				else {
					cout << "Wrong selection, try again\n";
				}
			} while (true);

			cout << deleteMovie << " Movie deleted\n\n";
			cout << "\n#\tName\t\t\t\tGenre\t\t\t\tRating\n\n";
			printListOfMovie(arr, quantityMovie);
		}
		else {
			cout << "Wrong selection, try again\n";
		}

	} while (true);


	delete[] arr;
}