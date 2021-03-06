// ZABRModel.cpp : Defines the entry point for the console application.
//

/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*!
Copyright (C) 2008 Florent Grenier

This file is part of QuantLib, a free-software/open-source library
for financial quantitative analysts and developers - http://quantlib.org/

QuantLib is free software: you can redistribute it and/or modify it
under the terms of the QuantLib license.  You should have received a
copy of the license along with this program; if not, please email
<quantlib-dev@lists.sf.net>. The license is also available online at
<http://quantlib.org/license.shtml>.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*  This example shows how to set up a term structure and then price
some simple bonds. The last part is dedicated to peripherical
computations such as "Yield to Price" or "Price to Yield"
*/

#include <ql/qldefines.hpp>
#ifdef BOOST_MSVC
#  include <ql/auto_link.hpp>
#endif



#include <ql/instruments/bonds/zerocouponbond.hpp>
#include <ql/instruments/bonds/floatingratebond.hpp>
#include <ql/pricingengines/bond/discountingbondengine.hpp>
#include <ql/cashflows/couponpricer.hpp>
#include <ql/termstructures/yield/piecewiseyieldcurve.hpp>
#include <ql/termstructures/yield/bondhelpers.hpp>
#include <ql/termstructures/volatility/optionlet/constantoptionletvol.hpp>
#include <ql/indexes/ibor/euribor.hpp>
#include <ql/indexes/ibor/usdlibor.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/time/daycounters/actualactual.hpp>
#include <ql/time/daycounters/actual360.hpp>
#include <ql/time/daycounters/thirty360.hpp>
#include <ql/instruments/bonds/all.hpp>
#include <ql/experimental/all.hpp>
#include <boost/timer.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <iomanip>
#include <memory>


using namespace QuantLib;

#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib {

	Integer sessionId() { return 0; }

}
#endif


int main(int, char*[]) {

	try {
		const Real expiryTime = 10;
		const Real forward = 0.0325;
		const Real alpha = 0.0873;
		const Real beta = 0.7;
		const Real nu = 0.47;
		const Real rho = -0.47;
		const Real gamma = 0.0;
		const Real strike = 0.05;

		std::shared_ptr<ZabrModel> zabrModel(new ZabrModel(expiryTime, forward, alpha, beta, nu, rho, gamma));

		std::cout << "begin" << std::endl;
		std::cout << "full Fd Price:" << zabrModel->fullFdPrice(strike) << std::endl;
		std::cout << "localVolatility:" << zabrModel->localVolatility(forward) << std::endl;
		std::cout << "lognormalVolatility:" << zabrModel->lognormalVolatility(strike)<< std::endl;
		std::cout << "normalVolatility:" << zabrModel->normalVolatility(strike)<< std::endl;

		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "unknown error" << std::endl;
		return 1;
	}
}



