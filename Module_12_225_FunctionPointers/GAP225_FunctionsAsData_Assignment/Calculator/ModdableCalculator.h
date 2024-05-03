#pragma once

#include <functional>
#include <string>
#include <vector>

class ModdableCalculator
{
private:
	using FloatOperation = std::function<float(float&, float&)>;
	using NamedOperation = std::pair<std::string, FloatOperation>;
	using OperationList = std::vector<NamedOperation>;

private:
	static constexpr int kQuit = 0;

	OperationList m_supportedOperations;

public:
	ModdableCalculator();
	~ModdableCalculator();

	void AddOperation(FloatOperation operation, const std::string& description);
	void Run();

private:
	int GetMenuChoice();
	void GetOperands(float& left, float& right);
	float PerformOperation(float left, float right, int operationIndex) const;
};

