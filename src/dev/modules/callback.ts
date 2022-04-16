type List<T = any> = { [key: string]: T };

namespace Callback {
	const _add = Callback.addCallback;

	interface CallbackInfo<C = Function> {
		once: boolean;
		callback: C,
		priority: number;
	}

	const eventList: List<CallbackInfo[]> = {};
	function invoker(name: string) {
		return (...args: any[]) => {
			const curList = eventList[name];
			for (let i = 0; i < curList.length; i++) {
				const ev = curList[i];
				ev.callback(...args);
				if (ev.once)
					off(name, ev.callback);
			}
		}
	}

	function add(name: string, info: CallbackInfo) {
		if (eventList[name]) {
			const newList = [];
			let notAdded = true;
			for (const eventInfo of eventList[name]) {
				if (notAdded && eventInfo.priority > info.priority) {
					newList.push(info);
					notAdded = false;
				}
				newList.push(eventInfo);
			}
			if (notAdded) newList.push(info);
			eventList[name] = newList;
		} else {
			eventList[name] = [info];
			//@ts-ignore
			_add(name, invoker(name), -1);
		}
	}



	export function on(name: string, callback: Function, priority: number = 10) {
		add(name, {
			callback, priority,
			once: false
		});
	}
	export function once(name: string, callback: Function, priority: number = 10) {
		add(name, {
			callback, priority,
			once: true
		});
	}
	export function off(name: string, callback: Function) {
		eventList[name] = eventList[name].filter(event => event.callback != callback);
	}

	//@ts-ignore
	addCallback = on;
}
