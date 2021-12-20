#pragma once

class ITrapActionable abstract
{
public:
	ITrapActionable() = default;
	virtual ~ITrapActionable() = default;

	virtual void	DoAction() = 0;
};