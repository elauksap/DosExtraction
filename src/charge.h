/* C++ */

/**
 * @file   charge.h
 * @author Pasquale Claudio Africa <pasquale.africa@gmail.com>
 * @date   2014
 *
 * @brief Classes for computing total electric charge.
 *
 */

#ifndef CHARGE_H
#define CHARGE_H

#include "paramList.h"
#include "quadratureRule.h"
#include "typedefs.h"

/**
 * @class Charge
 *
 * @brief Abstract class providing methods to calculate total electric charge (the rhs in the Poisson equation).
 *
 */
class Charge
{
	public:
		/**
		 * @brief Default constructor (deleted since it is required to specify a @ref ParamList and a @ref QuadratureRule).
		 */
		Charge() = delete;
		/**
		 * @brief Constructor.
		 * @param[in] params : the list of simulation parameters;
		 * @param[in] rule   : a quadrature rule.
		 */
		Charge(const ParamList &, const QuadratureRule &);
		/**
		 * @brief Destructor (defaulted).
		 */
		virtual ~Charge() = default;
		
		/**
		 * @brief Compute the total charge.
		 * @param[in] phi : the electric potential @f$ \varphi @f$.
		 * @returns the total charge @f$ q \left[ C \right] @f$.
		 */
		virtual VectorXr  charge(const VectorXr & phi) = 0;
		/**
		 * @brief Compute the derivative of the total charge with respect to the electric potential.
		 * @param[in] phi : the electric potential @f$ \varphi @f$.
		 * @returns the derivative: @f$ \frac{\mathrm{d}q}{\mathrm{d}\varphi} \left[ C \cdot V^{-1} \right] @f$.
		 */
		virtual VectorXr dcharge(const VectorXr & phi) = 0;
		
	protected:
		const ParamList      & params_;	/**< @brief Parameter list handler. */
		const QuadratureRule & rule_  ;	/**< @brief Quadrature rule handler. */
};

/**
 * @class GaussianCharge
 *
 * Provide methods to compute total electric charge and its derivative under the hypothesis that Density of States
 * is a linear combination of multiple gaussians, whose parameters are read from a @ref ParamList object.
 *
 * @brief Class derived from @ref Charge, under the hypothesis that Density of States is a combination of gaussians.
 *
 */
class GaussianCharge : public Charge
{
	public:
		/**
		 * @brief Default constructor (deleted since it is required to specify a @ref ParamList and a @ref QuadratureRule).
		 */
		GaussianCharge() = delete;
		/**
		 * @brief Constructor.
		 * @param[in] params : the list of simulation parameters;
		 * @param[in] rule   : a quadrature rule.
		 */
		GaussianCharge(const ParamList &, const QuadratureRule &);
		/**
		 * @brief Destructor (defaulted).
		 */
		virtual ~GaussianCharge() = default;
		
		virtual VectorXr  charge(const VectorXr &) override;
		virtual VectorXr dcharge(const VectorXr &) override;
		
	private:
		/**
		 * @brief Compute electrons density (per unit volume).
		 * @param[in] phi   : the electric potential @f$ \varphi @f$;
		 * @param[in] N0    : the gaussian mean @f$ N_0 @f$;
		 * @param[in] sigma : the gaussian standard deviation @f$ \sigma @f$.
		 * @returns the electrons density @f$ n(\varphi) \left[ m^{-3} \right] @f$.
		 */
		Real  n_approx(const Real &, const Real &, const Real &) const;
		/**
		 * @brief Compute the approximate derivative of electrons density (per unit volume)
		 * with respect to the electric potential.
		 * @param[in] phi   : the electric potential @f$ \varphi @f$;
		 * @param[in] N0    : the gaussian mean @f$ N_0 @f$;
		 * @param[in] sigma : the gaussian standard deviation @f$ \sigma @f$.
		 * @returns the derivative: @f$ \frac{\mathrm{d}n}{\mathrm{d}\varphi} \left[ m^{-3} \cdot V^{-1} \right] @f$.
		 */
		Real dn_approx(const Real &, const Real &, const Real &) const;
};

#endif /* CHARGE_H */
