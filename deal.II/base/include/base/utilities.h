//---------------------------------------------------------------------------
//    $Id$
//    Version: $Name$
//
//    Copyright (C) 2005, 2006, 2007, 2008 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//---------------------------------------------------------------------------
#ifndef __deal2__utilities_h
#define __deal2__utilities_h

#include <base/config.h>
#include <base/exceptions.h>

#include <vector>
#include <utility>
#include <string>

#if defined(DEAL_II_COMPILER_SUPPORTS_MPI) || defined(DEAL_II_USE_PETSC)
#include <mpi.h>
#else
typedef int MPI_Comm;
#endif

#ifdef DEAL_II_USE_TRILINOS
#  include <Teuchos_RCP.hpp>
#  include <Epetra_Comm.h>
#  ifdef DEAL_II_COMPILER_SUPPORTS_MPI
#    include <Epetra_MpiComm.h>
#  else
#    include <Epetra_SerialComm.h>
#  endif
#endif

DEAL_II_NAMESPACE_OPEN


/**
 * A namespace for utility functions that are not particularly specific to
 * finite element computing or numerical programs, but nevertheless are needed
 * in various contexts when writing applications.
 *
 * @ingroup utilities
 * @author Wolfgang Bangerth, 2005
 */
namespace Utilities
{

                                   /**
                                    * Convert a number @p i to a string, with
                                    * as many digits as given to fill with
                                    * leading zeros.
				    *
				    * If the second parameter is left at its
				    * default value, the number is not padded
				    * with leading zeros. The result is then
				    * the same as of the standard C function
				    * <code>itoa()</code> had been called.
                                    */
  std::string
  int_to_string (const unsigned int i,
		 const unsigned int digits = numbers::invalid_unsigned_int);

                                   /**
                                    * Determine how many digits are needed to
                                    * represent numbers at most as large as
                                    * the given number.
                                    */
  unsigned int
  needed_digits (const unsigned int max_number);

                                   /**
                                    * Given a string, convert it to an
                                    * integer. Throw an assertion if that is
                                    * not possible.
                                    */
  int
  string_to_int (const std::string &s);


                                   /**
                                    * Given a list of strings, convert it to a
                                    * list of integers. Throw an assertion if
                                    * that is not possible.
                                    */
  std::vector<int>
  string_to_int (const std::vector<std::string> &s);

                                   /**
                                    * Given a string that contains text
                                    * separated by a @p delimiter, split it into
                                    * its components; for each component,
                                    * remove leading and trailing spaces.
                                    *
                                    * The default value of the delimiter is a
                                    * comma, so that the function splits comma
                                    * separated lists of strings.
                                    */
  std::vector<std::string>
  split_string_list (const std::string &s,
                     const char         delimiter = ',');

                                   /**
                                    * Take a text, usually a documentation or
                                    * something, and try to break it into
                                    * individual lines of text at most @p
                                    * width characters wide, by breaking at
                                    * positions marked by @p delimiter in the text.
                                    * If this is not possible, return the shortest
                                    * lines than are longer than @p width.
                                    * The default value of the delimiter is a
                                    * space character.
                                    */
  std::vector<std::string>
  break_text_into_lines (const std::string &original_text,
                         const unsigned int width,
                         const char delimiter = ' ');

				   /**
				    * Return true if the given pattern
				    * string appears in the first
				    * position of the string.
				    */
  bool
  match_at_string_start (const std::string &name,
			 const std::string &pattern);

				   /**
				    * Read a (signed) integer starting
				    * at the position in @p name
				    * indicated by the second
				    * argument, and retun this integer
				    * as a pair together with how many
				    * characters it takes up in the
				    * string.
				    *
				    * If no integer can be read at the
				    * indicated position, return
				    * (-1,numbers::invalid_unsigned_int)
				    */
  std::pair<int, unsigned int>
  get_integer_at_position (const std::string &name,
			   const unsigned int position);
    
                                   /**
                                    * Generate a random number from a
                                    * normalized Gaussian probability
                                    * distribution centered around @p a and
                                    * with standard deviation @p sigma.
                                    */
  double
  generate_normal_random_number (const double a,
				 const double sigma);


				   /**
				    * Calculate a fixed power, provided as a
				    * template argument, of a number.
				    *
				    * This function provides an efficient way
				    * to calculate things like
				    * <code>t^N</code> where <code>N</code> is
				    * a known number at compile time.
				    *
				    * Use this function as in
				    * <code>fixed_power@<dim@> (n)</code>.
				    */
  template <int N, typename T>
  T
  fixed_power (const T t);
  
                                   /**
                                    * A namespace for utility functions that
                                    * probe system properties.
                                    * 
                                    * @ingroup utilities
                                    */
  namespace System
  {
    
                                     /**
                                      * Return the CPU load as returned by
                                      * "uptime". Note that the interpretation
                                      * of this number depends on the actual
                                      * number of processors in the
                                      * machine. This is presently only
                                      * implemented on Linux, using the
                                      * /proc/loadavg pseudo-file, on other
                                      * systems we simply return zero.
                                      */
    double get_cpu_load ();


                                     /**
                                      * Return the name of the host this
                                      * process runs on.
                                      */
    std::string get_hostname ();


                                     /**
                                      * Return the present time as HH:MM:SS.
                                      */
    std::string get_time ();

				     /**
				      * Return the number of MPI processes
				      * there exist. If this is a sequential
				      * job, it returns 1.
				      */
    unsigned int get_n_mpi_processes (const MPI_Comm &mpi_communicator);

				     /**
				      * Return the number of the
				      * present MPI process in the
				      * space of processes. This will
				      * be a unique value for each
				      * process between zero and (less
				      * than) the number of all
				      * processes (given by
				      * get_n_mpi_processes()).
				      *
				      * This function will only work if you
				      * also configured the library to use
				      * PETSc. If your program uses MPI but
				      * not PETSc, then this function is
				      * likely not going to work.
				      */
    unsigned int get_this_mpi_process (const MPI_Comm &mpi_communicator);
  }



  /**
   * This class provides the basic structures for the use of the
   * Trilinos classes such as matrices, vectors, and
   * preconditioners. The most important function in this class is
   * <tt>comm()</tt>, which is needed for the initialization of
   * Trilinos Epetra_Maps, which design the parallel distribution of
   * vectors and matrices. Moreover, this class provides a unified
   * interface to both serial and parallel implementations of
   * Trilinos, sets up the MPI communicator in case the programs are
   * run in parallel, and correctly terminates all processes when the
   * destructor is called. An example usage of this class is shown in
   * @ref step_32 step-32.
   */
#ifdef DEAL_II_USE_TRILINOS
  class TrilinosTools
  {
    public:
				     /**
				      * Constructor. Takes the
				      * arguments from the command
				      * line (in case of MPI, the
				      * number of processes is
				      * specified there), and sets up
				      * a respective communicator by
				      * calling <tt>MPI_Init()</tt>.
				      */
      TrilinosTools (int*    argc,
		     char*** argv);

				     /**
				      * Copy constructor. Takes the
				      * Trilinos communicator from the
				      * input object and copies all
				      * content. Note that the copied
				      * class cannot own the MPI
				      * process, and hence, the
				      * original object needs to be
				      * around as long as the copy.
				      */
      TrilinosTools(const TrilinosTools &InputTrilinos);

				     /**
				      * Destructor. Calls
				      * <tt>MPI_Finalize()</tt> in
				      * case this class owns the MPI
				      * process.
				      */
      ~TrilinosTools();

				     /**
				      * Returns a Trilinos Epetra_Comm
				      * object needed for creation of
				      * Epetra_Maps.
				      */
      const Epetra_Comm& comm() const;

				     /**
				      * Returns whether we are using a
				      * MPI version or a serial
				      * version of Trilinos.
				      */
      bool trilinos_uses_mpi() const;

    private:
				     /**
				      * This flag tells the class
				      * whether it owns the MPI
				      * process (i.e., it has been
				      * constructed using the
				      * argc/argv input, or it has
				      * been copied). In the former
				      * case, the command
				      * <tt>MPI_Finalize()</tt> will
				      * be called at destruction.
				      */
      const bool owns_mpi;

				     /**
				      * This flag tells whether we use
				      * MPI or not.
				      */
      const bool use_mpi;

				     /**
				      * The actual communicator
				      * object. If we run the program
				      * in serial, we will have
				      * another communicator than when
				      * running in parallel.
				      */
#ifdef DEAL_II_COMPILER_SUPPORTS_MPI
      Teuchos::RCP<Epetra_MpiComm> communicator;
#else
      Teuchos::RCP<Epetra_SerialComm> communicator;
#endif
  };

#endif

}


// --------------------- inline functions

namespace Utilities
{
  template <int N, typename T>
  inline
  T fixed_power (const T n)
  {
    Assert (N>0, ExcNotImplemented());
    switch (N)
      {
	case 1:
	      return n;
	case 2:
	      return n*n;
	case 3:
	      return n*n*n;
	case 4:
	      return n*n*n*n;
	default:
	      T result = n;  
	      for (unsigned int d=1;d<N;++d)
		result *= n;
	      return result;
      }
  }
  
}


DEAL_II_NAMESPACE_CLOSE

#endif

