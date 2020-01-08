// Copyright 2019 Fedorov james.sayfer2015@yandex.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <utility>
#include <stddef.h>

class CntP
{
private:
    std::atomic<int> cnt;

public:
    CntP() : cnt(0) {}


    explicit CntP(int cou) : cnt(cou) {}

    int getCnt() const
	{
        return cnt;
    }

    void incr()
	{
        cnt=cnt+1;
    }


    void decr()
	{
        cnt=cnt-1;
    }


    bool operator==(const int& pam) const
	{
        if (cnt == pam)
		{
            return true;
        }
		else
		{
            return false;
        }
    }
};


template <typename T>
class SharedPtr
{
public:
    SharedPtr()
	{
        data = nullptr;
        numb = nullptr;
    }


    explicit SharedPtr(T* pam)
	{
        data = pam;
        numb = new CntP(1);
    }


    SharedPtr(const SharedPtr& r)
	{
        data = r.data;
        numb = r.numb;
        if (numb != nullptr)
		{
			numb->incr();
		}
    }


    SharedPtr(SharedPtr&& r)
	{
        data = r.data;
        numb = r.numb;
        if (numb != nullptr)
		{
			numb->incr();
		}
    }


    ~SharedPtr()
	{
        if (numb != nullptr)
		{
            numb->decr();
            if (*numb == 0)
			{
                delete numb;
                delete data;
            }
        }
    }

    operator bool() const
	{
        if (numb == nullptr)
		{
            return false;
        }
		else
		{
            return true;
        }
    }

    auto operator=(const SharedPtr& r)->SharedPtr&
	{
        if (numb != nullptr)
		{
            numb->decr();
            if (*numb == 0)
			{
                delete numb;
                delete data;
            }
        }
        numb = r.numb;
        data = r.data;
        if (numb != nullptr)
		{
			numb->incr();
		}
        return *this;
    }


    auto operator=(SharedPtr&& r)->SharedPtr&
	{
        if (numb != nullptr)
		{
            numb->decr();
            if (*numb == 0)
			{
                delete numb;
                delete data;
            }
        }
        numb = r.numb;
        data = r.data;
        if (numb != nullptr)
		{
			numb->incr();
		}
        return *this;
    }



    auto get()->T*
	{
        return data;
    }

    auto operator*() const->T&
	{
        return *data;
    }


    auto operator->() const->T*
	{
        return data;
    }




    void reset()
	{
        if (numb == nullptr)
		{
			return;
		}
        numb->decr();
        if (*numb == 0)
		{
            delete numb;
            delete data;
        }
        numb = nullptr;
        data = nullptr;
    }

    auto useCnt() const->size_t
	{
        if (numb == nullptr)
		{
			return 0;
		}
        return static_cast<size_t>(numb->getCnt());
    }

    void reset(T* ptr)
	{
        if (numb != nullptr)
		{
            numb->decr();
            if (*numb == 0)
			{
                delete numb;
                delete data;
            }
        }
        data = ptr;
        numb = new CntP(1);
    }


    void swap(SharedPtr& r)
	{
        if (data == r.data)
		{
			return;
		}
        std::swap(numb, r.numb);
        std::swap(data, r.data);
    }


private:
    T* data;
    CntP* numb;
};
#endif // INCLUDE_HEADER_HPP_
