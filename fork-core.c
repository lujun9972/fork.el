#include <unistd.h>
#include <emacs-module.h>

/* 强制申明GPL符号 */
int plugin_is_GPL_compatible;

/* 定义新emacs lisp函数. 所有暴露給Emacs使用的函数都必须符合该原型 */
static emacs_value
Ffork_core (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
  int pid = fork();
  return env->make_integer (env, pid);
}

/* 将函数Sfun以name为名称,暴露給emacs使用 */
static void
bind_function (emacs_env *env, const char *name, emacs_value Sfun)
{
  /* 使用fset函数来将SFUN函数绑定到名为NAME的符号 */

  /* 通过intern将字符串转换为symbol */
  emacs_value Qfset = env->intern (env, "fset");
  emacs_value Qsym = env->intern (env, name);

  /* 准备好参数数组*/
  emacs_value args[] = { Qsym, Sfun };

  /* 调用fset函数,这里的2为参数的个数*/
  env->funcall (env, Qfset, 2, args);
}

/* Provide FEATURE to Emacs.  */
static void
provide (emacs_env *env, const char *feature)
{
  /* call 'provide' with FEATURE converted to a symbol */

  emacs_value Qfeat = env->intern (env, feature);
  emacs_value Qprovide = env->intern (env, "provide");
  emacs_value args[] = { Qfeat };

  env->funcall (env, Qprovide, 1, args);
}

int
emacs_module_init (struct emacs_runtime *ert)
{
  emacs_env *env = ert->get_environment (ert);

  /* 创建匿名函数,该匿名函数被封装成一个emacs_value*/
  emacs_value fun = env->make_function (env,
              0,            /* 最少需要的参数个数*/
              0,            /* 支持的最大参数个数*/
              Ffork_core,        /* 实际函数的指针*/
              "fork - create a child process", /* docstring */
              NULL          /* user pointer of your choice (data param in Ffork_core) */
  );

  bind_function (env, "fork", fun);
  provide (env, "fork-core");

  /* loaded successfully */
  return 0;
}
