#pragma once
#ifndef _ENGINE_DEFINITIONS_H_
#define _ENGINE_DEFINITIONS_H_
// Copyright © 2023 UNKNOWN STRYKER. All Rights Reserved
// Copyright © 2023 Hojin Lee. All Rights Reserved
// Copyright © 2023 Joey Hojin Lee. All Rights Reserved
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

#define _NODISCARD_ [[nodiscard]]
#define _FALLTHROUGH_ [[fallthrough]]
#define _MAYBE_UNUSED_ [[maybe_unused]]
#define _NORETURN_ [[noreturn]]
#define _DEPRECATED_ [[deprecated]]
#define _LIKELY_ [[likely]]
#define _UNLIKELY_ [[unlikely]]
#define _IN_DEVELOPMENT_ _DEPRECATED_

#define exit_loop goto

#define BEGIN namespace
#define NAMESPACE(NAME_P) NAME_P {
#define END_NAMESPACE }
#define END_FSTD }

#define STDCALL __stdcall
#define _FORCE_INLINE_ __forceinline
#define FROGMAN_ENGINE_API __declspec( dllexport )

#define _8BIT_CACHE_LINE_SIZE_ 8
#define _16BIT_CACHE_LINE_SIZE_ 16
#define _32BIT_CACHE_LINE_SIZE_ 32
#define _64BIT_CACHE_LINE_SIZE_ 64

#endif