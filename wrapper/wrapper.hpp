#pragma once

#include "..\common\error.hpp"
#include "wrapper_writer.hpp"
#include <iostream>
using namespace rawaccel;
using namespace System;

public ref class ManagedAccel
{
protected:
	mouse_modifier* modifier_instance;
    writer* driverWriter;
public:
	ManagedAccel(mouse_modifier* accel)
		: modifier_instance(accel)
	{
	}

    ManagedAccel(int mode, double offset, double accel, double lim_exp, double midpoint)
    {
        modifier_args args{};
        args.acc_fn_args.acc_args.accel = accel;
        args.acc_fn_args.acc_args.lim_exp = lim_exp;
        args.acc_fn_args.acc_args.midpoint = midpoint;
        args.acc_fn_args.accel_mode = mode;
        args.acc_fn_args.acc_args.offset = offset;

		modifier_instance = new mouse_modifier(args);
        driverWriter = new writer();
	}

    virtual ~ManagedAccel()
    {
        if (modifier_instance!= nullptr)
        {
            delete modifier_instance;
        }
    }
    !ManagedAccel()
    {
        if (modifier_instance!= nullptr)
        {
            delete modifier_instance;
        }
    }

    mouse_modifier* GetInstance()
    {
        return modifier_instance;
    }

    Tuple<double, double>^ Accelerate(int x, int y, double time);

    void UpdateAccel(
        int mode,
        double sensitivityX,
        double sensitivityY,
        double weightX,
        double weightY,
        double capX,
        double capY,
        double offset,
        double accel,
        double lim_exp,
        double midpoint);


    void WriteToDriver();
};