/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/// @file src/base/managers/tracer/MasalaTracerManager.cc
/// @brief A static singleton for managing output to the tracer (screen and/or logfile(s)).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/tracer/MasalaTracerManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/utility/string/string_manipulation.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace tracer {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaTracerManagerHandle
MasalaTracerManager::get_instance() {
	static MasalaTracerManager config_manager;
	return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Default destructor.
MasalaTracerManager::~MasalaTracerManager() {
	// Print the Masala citation when we destroy this tracer.
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	if( using_mpi_ == false || mpi_process_rank_ == 0 ) {
		if( output_stream_ == nullptr ) {
			//            xxxxxxxx                   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
			std::cout << "MASALA: " << "\033[1;33;41mThank you for using the Masala software suite.  If you publish results. \033[0m\n";
			std::cout << "MASALA: " << "\033[1;33;41mobtained with Masala, please cite the following preprint:               \033[0m\n";
			std::cout << "MASALA: " << "\033[1;33;41m                                                                        \033[0m\n";
			std::cout << "MASALA: " << "\033[1;33;41mT. Zaborniak, N. Azadvari, Q. Zhu, S.M.B.A. Turzo, P. Hosseinzadeh, P.D.\033[0m\n";
			std::cout << "MASALA: " << "\033[1;33;41mRenfrew, and V.K. Mulligan.  (2025).  The open-source Masala software.  \033[0m\n";
			std::cout << "MASALA: " << "\033[1;33;41msuite: Facilitating rapid methods development for synthetic             \033[0m\n";
			std::cout << "MASALA: " << "\033[1;33;41mheteropolymer design. bioRxiv https://doi.org/10.1101/2025.07.02.662756.\033[0m" << std::endl;
			std::cout.flush();
		} else {
			(*output_stream_) << "MASALA: " << "\033[1;33;41mThank you for using the Masala software suite.  If you publish results. \033[0m\n";
			(*output_stream_) << "MASALA: " << "\033[1;33;41mobtained with Masala, please cite the following preprint:               \033[0m\n";
			(*output_stream_) << "MASALA: " << "\033[1;33;41m                                                                        \033[0m\n";
			(*output_stream_) << "MASALA: " << "\033[1;33;41mT. Zaborniak, N. Azadvari, Q. Zhu, S.M.B.A. Turzo, P. Hosseinzadeh, P.D.\033[0m\n";
			(*output_stream_) << "MASALA: " << "\033[1;33;41mRenfrew, and V.K. Mulligan.  (2025).  The open-source Masala software.  \033[0m\n";
			(*output_stream_) << "MASALA: " << "\033[1;33;41msuite: Facilitating rapid methods development for synthetic             \033[0m\n";
			(*output_stream_) << "MASALA: " << "\033[1;33;41mheteropolymer design. bioRxiv https://doi.org/10.1101/2025.07.02.662756.\033[0m" << std::endl;
			output_stream_->flush();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaTracerManager".
std::string
MasalaTracerManager::class_name() const {
	return "MasalaTracerManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::tracer".
std::string
MasalaTracerManager::class_namespace() const {
	return "masala::base::managers::tracer";
}

/// @brief If we want to direct output to something other than std::cout, we can provide a shared pointer
/// to a std::ostream object.
/// @param output_stream_pointer A shared pointer to a std::ostream object guaranteed to persist through program execution
/// (or as long as we use this output stream).  The shared pointer (but not the stream object) is copied on input.
void
MasalaTracerManager::set_redirect_tracers(
	std::shared_ptr< std::ostream > const & output_stream_pointer
) {
	CHECK_OR_THROW_FOR_CLASS( output_stream_pointer != nullptr, "set_redirect_tracers", "A null pointer was passed to this function." );
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	output_stream_ = output_stream_pointer;
}

/// @brief Reset the output to flow to std::cout instead of to any custom std::ostream provided previously.
void
MasalaTracerManager::reset_redirect_tracers() {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	output_stream_ = nullptr;
}

/// @brief Check whether a particular tracer is enabled.
/// @details If the tracer is in the list of tracers specifically enabled or disabled, the
/// tracer's status is returned.  Otherwise, the global default is returned.
bool
MasalaTracerManager::tracer_is_enabled(
	std::string const & tracer_name
) const {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	std::map< std::string, bool >::const_iterator it( explicitly_enabled_or_disabled_tracers_.find( tracer_name ) );
	if( it != explicitly_enabled_or_disabled_tracers_.end() ) {
		return it->second;
	}
	return global_tracer_default_;
}

/// @brief Set whether a particular tracer is explicitly enabled or disabled.  True means
/// enabled, false means disabled.
/// @details Can be undone with reset_tracer_state().
void
MasalaTracerManager::set_tracer_state(
	std::string const & tracer_name,
	bool const setting
) {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	explicitly_enabled_or_disabled_tracers_[tracer_name] = setting;
}

/// @brief Remove the explicit specification for whether a particular tracer is enabled or
/// disabled.  This reverts the tracer behaviour back to the global setting.
void
MasalaTracerManager::reset_tracer_state(
	std::string const & tracer_name
) {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	std::map< std::string, bool >::iterator it( explicitly_enabled_or_disabled_tracers_.find( tracer_name ) );
	if( it != explicitly_enabled_or_disabled_tracers_.end() ) {
		explicitly_enabled_or_disabled_tracers_.erase(it);
	}
}

/// @brief Check whether the global default for unspecified tracers is enabled or disabled.
bool
MasalaTracerManager::global_tracer_default() const {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	return global_tracer_default_;
}

/// @brief Set whether the global default for unspecified tracers is enabled or disabled.
void
MasalaTracerManager::set_global_tracer_default(
	bool const setting
) {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	global_tracer_default_ = setting;
}

/// @brief Write a message to a tracer.
/// @param tracer_name The tracer to which we are writing.
/// @param message The text that we are writing.  This gets split by lines, with each line preceded
/// by the tracer name.
/// @param skip_check If true, we don't bother to check whether the tracer is enabled.  If false, we
/// check and skip writing if the tracer is disabled.  Default false.
void
MasalaTracerManager::write_to_tracer(
	std::string const & tracer_name,
	std::string const & message,
	bool const skip_check /*= false*/
) const {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );

	// Check whether the tracer is enabled:
	if( !skip_check ) {
		std::map< std::string, bool >::const_iterator it( explicitly_enabled_or_disabled_tracers_.find( tracer_name ) );
		if( it != explicitly_enabled_or_disabled_tracers_.end() ) {
			if( !(it->second) ) {
				return;
			}
		} else {
			if( !global_tracer_default_ ) {
				return;
			}
		}
	}

	// Write the message to the tracer.
	std::vector< std::string > const splitlines( masala::base::utility::string::split_by_newlines( message ) );
	if( output_stream_ == nullptr  ) {
		for( masala::base::Size i(0), imax(splitlines.size()); i<imax; ++i ) {
			if( using_mpi_ ) {
				std::cout << tracer_name << "{P" << mpi_process_rank_ << "-T" << get_thread_id_string() << "}: " << splitlines[i] << "\n";
			} else {
				std::cout << tracer_name << "{T" << get_thread_id_string() << "}: " << splitlines[i] << "\n";
			}
		}
		std::cout.flush();
	} else {
		for( masala::base::Size i(0), imax(splitlines.size()); i<imax; ++i ) {
			if( using_mpi_ ) {
				( *output_stream_ ) << tracer_name << "{P" << mpi_process_rank_ << "-T" << get_thread_id_string() << "}: " << splitlines[i] << "\n";
			} else {
				( *output_stream_ ) << tracer_name << "{T" << get_thread_id_string() << "}: " << splitlines[i] << "\n";
			}
		}
		(*output_stream_).flush();
	}
}

/// @brief Get the string for the current thread's ID.
std::string
MasalaTracerManager::get_thread_id_string() const {
	std::lock_guard< std::mutex > lock( thread_map_mutex_ );
#ifdef MASALA_MPI
	TODO TODO TODO; // Will trigger compilation error if support for stamping logfile lines by MPI process is not implemented.
#endif
	if( thread_map_.empty() ) {
		return "0";
	}
	std::map< std::thread::id, base::Size >::const_iterator it( thread_map_.find( std::this_thread::get_id() ) );
	if( it == thread_map_.end() ) {
		return "?";
	}
	return std::to_string( it->second );
} // MasalaTracerManager::get_thread_id_string()

/// @brief Register thread ID with the tracer manager.
void
MasalaTracerManager::register_thread_id(
	std::thread::id const system_thread_id,
	base::Size const masala_thread_id
) {   
	std::lock_guard< std::mutex > lock( thread_map_mutex_ );
	thread_map_[system_thread_id] = masala_thread_id;
} // MasalaTracerManager::register_thread_id()

/// @brief Unregister thread ID with the tracer manager.
void
MasalaTracerManager::unregister_thread_id(
	std::thread::id const system_thread_id
) {
	std::lock_guard< std::mutex > lock( thread_map_mutex_ );
	std::map< std::thread::id, base::Size >::iterator it( thread_map_.find( system_thread_id ) );
	thread_map_.erase(it);
} // MasalaTracerManager::unregister_thread_id()

////////////////////////////////////////////////////////////////////////////////
// ADVANCED API PUBLIC MEMBER FUNCTIONS
// These require an instance of a MasalaTracerManagerAccessKey.  Since only
// certain managers can instantiate this class, this ensures that only these
// classes may call these functions.
////////////////////////////////////////////////////////////////////////////////

/// @brief Indicate that we are using MPI, and set the current MPI rank.
/// @details In addition to setting the MPI rank, this sets using_mpi_ to true.
/// @note This requires an instance of a MasalaTracerManagerAccessKey.  Since only
// certain managers can instantiate this class, this ensures that only these
// classes may call these functions.
void
MasalaTracerManager::set_mpi_rank(
	masala::base::Size const rank_in,
	MasalaTracerManagerAccessKey const & /*access_key*/
) {
	std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
	using_mpi_ = true;
	mpi_process_rank_ = rank_in;
}

} // namespace tracer
} // namespace managers
} // namespace base
} // namespace masala
