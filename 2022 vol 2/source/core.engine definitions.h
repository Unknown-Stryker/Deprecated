#ifndef _ENGINE_DEFINITIONS_H_
#define _ENGINE_DEFINITIONS_H_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved. UNKNOWN STRYKER is Hojin Lee
#include <vcruntime.h>
#if _HAS_CXX17 == 1
#include "core.flags.h"

#define constructors public
#define protected_constructors protected
#define private_constructors private
#define destructor public

#define copy_constructor public
#define protected_copy_constructor protected
#define private_copy_constructor private

#define move_constructor public
#define protected_move_constructor protected
#define private_move_constructor private

#define member_variables private
#define protected_member_variables protected

#define methods public
#define protected_methods protected
#define internal_methods private

#define friend_methods public

#define static_methods public
#define protected_static_methods protected
#define private_static_methods private

#define recursive public
#define protected_recursive protected
#define private_recursive private

#define operators public
#define protected_operators protected
#define private_operators private

#define assignment_operator public
#define protected_assignment_operator protected
#define private_assignment_operator private

#define copy_assignment_operator public
#define protected_copy_assignment_operator protected
#define private_copy_assignment_operator private

#define move_assignment_operator public
#define protected_move_assignment_operator protected
#define private_move_assignment_operator private

#define abstract_class class

#define field_variables public

#define _NODISCARD_ [[nodiscard]]
#define _FALLTHROUGH_ [[fallthrough]]
#define _MAYBE_UNUSED_ [[maybe_unused]]
#define _NORETURN_ [[noreturn]]
#define _DEPRECATED_ [[deprecated]]

#if _HAS_CXX20 == 1
#define _LIKELY_ [[likely]]
#define _UNLIKELY_ [[unlikely]]
#endif

#define _IN_DEVELOPMENT_ _DEPRECATED_

#define _EXIT_LOOP_ goto

#define BEGIN_NAMESPACE(NAME_P) namespace NAME_P {
#define END_NAMESPACE }
#define END_FE }

#define _STDCALL_ __stdcall
#define _FORCE_INLINE_ __forceinline
#define _FROGMAN_ENGINE_API_ __declspec( dllexport )

#endif
#endif