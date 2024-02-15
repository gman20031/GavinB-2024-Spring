
#include<functional>
#include<iostream>

class Button
{
	std::function<void()> m_onClick;

public:
	Button(std::function<void()> onClick)
		: m_onClick(onClick)
	{ }

	void Click()
	{
		m_onClick();
	}
};

static void ShowCat()
{
	std::cout << "Cat\n";
}

int main()
{
	Button catButton(&ShowCat);

	catButton.Click();

	return 0;
}