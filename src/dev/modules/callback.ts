type List<T = any> = { [key: string]: T };

namespace Callback {

	const _add = Callback.addCallback;

	interface CallbackInfo<C = Function> {
		once: boolean,
		callback: C,
		priority: number;
	}

	const eventList: List<CallbackInfo[]> = {};

	function invoker(name: string): Function {
		return (...args: any[]) => {
			eventList[name] ??= [];
			const curList = eventList[name];
			curList.forEach(ev => {
				ev.callback(...args);
				if(ev.once) off(name, ev.callback);
			});
		}
	}

	function add(name: string, info: CallbackInfo): void {
		if(eventList[name]) {
			const newList = [];
			let notAdded: boolean = true;
			for(const eventInfo of eventList[name]) {
				if(notAdded && eventInfo.priority > info.priority) {
					newList.push(info);
					notAdded = false;
				}
				newList.push(eventInfo);
			}
			if(notAdded) newList.push(info);
			eventList[name] = newList;
		} else {
			eventList[name] = [ info ];
			_add(name, invoker(name), -1);
		}
	}

	export var on: typeof addCallback = (name: string, callback: Function, priority?: number) => add(name, { callback, priority, once: false });
	export var once: typeof addCallback = (name: string, callback: Function, priority?: number) => add(name, { callback, priority, once: true });
	export var off: typeof addCallback = (name: string, callback: Function) => eventList[name] = eventList[name].filter(event => event.callback != callback);

}

Callback.addCallback = Callback.on;