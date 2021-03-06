// ---------------------------------------------------------------------
//
// Copyright (C) 2009 - 2017 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------

#ifndef dealii_distributed_grid_refinement_h
#define dealii_distributed_grid_refinement_h


#include <deal.II/base/config.h>
#include <deal.II/base/exceptions.h>
#include <deal.II/distributed/tria.h>

#include <vector>
#include <limits>

DEAL_II_NAMESPACE_OPEN

namespace parallel
{
  namespace distributed
  {
    /**
     * This namespace provides a collection of functions that aid in refinement
     * and coarsening of triangulations. Despite the name of the namespace, the
     * functions do not actually <i>refine</i> the triangulation, but only
     * <i>mark cells for refinement or coarsening</i>. In other words, they
     * perform the "mark" part of the typical "solve-estimate-mark-refine"
     * cycle of the adaptive finite element loop.
     *
     * In contrast to the functions in namespace dealii::GridRefinement,
     * the functions in the current namespace are intended for distributed
     * meshes, i.e., objects of type parallel::distributed::Triangulation.
     *
     * @ingroup grid
     * @author Wolfgang Bangerth, 2009
     */
    namespace GridRefinement
    {
      /**
       * Like dealii::GridRefinement::refine_and_coarsen_fixed_number, but for
       * parallel distributed triangulations.
       *
       * The vector of criteria needs to be a vector of refinement criteria
       * for all cells active on the current triangulation, i.e.,
       * it needs to be of length <code>tria.n_active_cells()</code> (and not
       * <code>tria.n_locally_owned_active_cells()</code>). In other words,
       * the vector needs to include entries for ghost and artificial
       * cells. However, the current
       * function will only look at the indicators that correspond to those
       * cells that are actually locally owned, and ignore the indicators for
       * all other cells. The function will then coordinate among all
       * processors that store part of the triangulation so that at the end
       * a fraction @p top_fraction_of_cells of all Triangulation::n_global_active_cells()
       * active cells are refined, rather than a fraction of the
       * Triangulation::n_locally_active_cells on each processor individually.
       * In other words, it may be that on some processors, no cells are
       * refined at all.
       *
       * The same is true for the fraction of cells that is coarsened.
       */
      template <int dim, typename Number, int spacedim>
      void
      refine_and_coarsen_fixed_number
      (parallel::distributed::Triangulation<dim,spacedim> &tria,
       const dealii::Vector<Number>                       &criteria,
       const double                                       top_fraction_of_cells,
       const double                                       bottom_fraction_of_cells,
       const unsigned int                                 max_n_cells = std::numeric_limits<unsigned int>::max());

      /**
       * Like dealii::GridRefinement::refine_and_coarsen_fixed_fraction, but
       * for parallel distributed triangulations.
       *
       * The vector of criteria needs to be a vector of refinement criteria
       * for all cells active on the current triangulation, i.e.,
       * it needs to be of length <code>tria.n_active_cells()</code> (and not
       * <code>tria.n_locally_owned_active_cells()</code>). In other words,
       * the vector needs to include entries for ghost and artificial
       * cells. However, the current
       * function will only look at the indicators that correspond to those
       * cells that are actually locally owned, and ignore the indicators for
       * all other cells. The function will then coordinate among all
       * processors that store part of the triangulation so that at the end
       * the smallest fraction of Triangulation::n_global_active_cells (not
       * Triangulation::n_locally_owned_active_cells() on each processor individually)
       * is refined that together make up a total of @p top_fraction_of_error
       * of the total error. In other words, it may be that on some
       * processors, no cells are refined at all.
       *
       * The same is true for the fraction of cells that is coarsened.
       */
      template <int dim, typename Number, int spacedim>
      void
      refine_and_coarsen_fixed_fraction
      (parallel::distributed::Triangulation<dim,spacedim> &tria,
       const dealii::Vector<Number>                       &criteria,
       const double                                       top_fraction_of_error,
       const double                                       bottom_fraction_of_error);
    }
  }
}


DEAL_II_NAMESPACE_CLOSE

#endif //dealii_distributed_grid_refinement_h
