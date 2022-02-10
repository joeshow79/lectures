; ModuleID = 'dax.c'
source_filename = "dax.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @dax(double* noalias %y, double %a, double* noalias %x, i64 %n) #0 {
entry:
  %y.addr = alloca double*, align 8
  %a.addr = alloca double, align 8
  %x.addr = alloca double*, align 8
  %n.addr = alloca i64, align 8
  %i = alloca i64, align 8
  store double* %y, double** %y.addr, align 8
  store double %a, double* %a.addr, align 8
  store double* %x, double** %x.addr, align 8
  store i64 %n, i64* %n.addr, align 8
  store i64 0, i64* %i, align 8
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8
  %1 = load i64, i64* %n.addr, align 8
  %cmp = icmp slt i64 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load double, double* %a.addr, align 8
  %3 = load double*, double** %x.addr, align 8
  %4 = load i64, i64* %i, align 8
  %arrayidx = getelementptr inbounds double, double* %3, i64 %4
  %5 = load double, double* %arrayidx, align 8
  %mul = fmul double %2, %5
  %6 = load double*, double** %y.addr, align 8
  %7 = load i64, i64* %i, align 8
  %arrayidx1 = getelementptr inbounds double, double* %6, i64 %7
  store double %mul, double* %arrayidx1, align 8
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %8 = load i64, i64* %i, align 8
  %inc = add nsw i64 %8, 1
  store i64 %inc, i64* %i, align 8
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.1 (https://github.com/OpenCilk/opencilk-project 8435006eea5d32f9cf895a666496b89613e2cbc1)"}
