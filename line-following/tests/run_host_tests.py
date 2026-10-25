"""Compile original application against inert host APIs; never starts firmware main."""
from pathlib import Path
import argparse, json, os, subprocess, tempfile

parser=argparse.ArgumentParser()
parser.add_argument('--cc',default=os.environ.get('CC','gcc'))
args=parser.parse_args()
root=Path(__file__).resolve().parents[1]
def run(command):
    p=subprocess.run([str(v) for v in command],capture_output=True,text=True,errors='replace',timeout=30)
    return {'command':[str(v) for v in command], 'returncode':p.returncode,'stdout':p.stdout,'stderr':p.stderr}
with tempfile.TemporaryDirectory(prefix='line_following_host_') as temp:
    temp=Path(temp)
    flags=['-std=c99','-Wall','-Wextra','-finput-charset=GB18030','-I'+str(root/'tests/host'),'-I'+str(root/'src')]
    compile_result=run([args.cc,*flags,root/'src/type.c',root/'tests/host/test_control.c','-o',temp/'test_control.exe','-lm'])
    # main.c only receives an alternate symbol name; its infinite hardware loop is never run.
    main_result=run([args.cc,*flags,'-Dmain=archived_firmware_main','-c',root/'src/main.c','-o',temp/'main.o'])
    if compile_result['returncode'] or main_result['returncode']:
        print(json.dumps({'compile':compile_result,'compile_main':main_result},indent=2));raise SystemExit(1)
    normal=run([temp/'test_control.exe'])
    bounded=run([temp/'test_control.exe','--over-max'])
    passed=normal['returncode']==0 and bounded['returncode']==42 and 'EXPECTED:' in bounded['stdout']
    # Paths in temporary compile commands are useful locally, but keep public results portable.
    print(json.dumps({'status':'pass' if passed else 'fail','validation':'host-only, no firmware or hardware execution',
        'compiler_warnings':compile_result['stderr']+main_result['stderr'],
        'normal':{'returncode':normal['returncode'],'stdout':normal['stdout'],'stderr':normal['stderr']},
        'persistent_over_max':{'returncode':bounded['returncode'],'stdout':bounded['stdout'],'stderr':bounded['stderr']},
        'timeout_seconds_per_process':30},indent=2))
    raise SystemExit(0 if passed else 1)
